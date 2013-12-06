// This file is part of CaesarIA.
//
// CaesarIA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CaesarIA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2013 Gregoire Athanase, gathanase@gmail.com


#include "engine.hpp"

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "game/settings.hpp"
#include "core/exception.hpp"
#include "core/logger.hpp"
#include "vfs/file.hpp"

namespace audio
{

struct Sample
{
  int channel;
  std::string sound;
  Mix_Chunk* chunk;
};

class Engine::Impl
{
public:
  static const int maxSamplesNumner = 64;
  bool useSound;

  typedef std::map< std::string, Sample > Samples;
  Samples samples;
};

Engine& Engine::instance()
{
   static Engine _instance;
   return _instance;
}

Engine::Engine() : _d( new Impl )
{
  _d->useSound = false;
}

Engine::~Engine()
{
}

void Engine::init()
{
  bool sound_ok = false;
  if( _d->useSound )
  {
     return;        // avoid init twice
  }

  // initialize SDL sound subsystem
  if (SDL_InitSubSystem(SDL_INIT_AUDIO) != -1)
  {
    // open an audio channel

    int freq = 22050;
    int channels = 1;
    unsigned short int format = AUDIO_S16SYS;
    int samples = 1024;

    if (Mix_OpenAudio(freq, format, channels, samples) != -1)
    {
      Mix_QuerySpec(&freq, &format, &channels);
      // check if we got the right audi format
      if (format == AUDIO_S16SYS)
      {
        // finished initializing
        sound_ok = true;

        // allocate 16 mixing channels
        Mix_AllocateChannels(16);

        // start playing sounds
        Mix_ResumeMusic();
      }
      else
      {
        Logger::warning( "Open audio channel doesn't meet requirements. Muting" );
        Mix_CloseAudio();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
      }
    }
    else
    {
      Logger::warning( "Could not open required audio channel. Muting ");
      SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
  }
  else
  {
    Logger::warning( "Could not initialize sound system. Muting ");
  }

  _d->useSound = sound_ok;
}


void Engine::exit()
{
   Mix_CloseAudio();
}

bool Engine::load(vfs::Path filename)
{
  if(_d->useSound>0 && _d->samples.size()<Impl::maxSamplesNumner)
  {
    Impl::Samples::iterator i = _d->samples.find( filename.toString() );

    if( i != _d->samples.end() )
    {
      return true;
    }

    Sample sample;

    /* load the sample */
    vfs::NFile wavFile = vfs::NFile::open( filename );
    ByteArray data = wavFile.readAll();

    if( data.empty() )
    {
      return false;
    }

    sample.channel = -1;
    sample.chunk = Mix_LoadWAV_RW( SDL_RWFromMem( data.data(), data.size() ), 1 );
    sample.sound = filename.toString();
    if(sample.chunk == NULL)
    {
      Logger::warning( "could not load wav (%s)", SDL_GetError() );
      return false;
    }

    _d->samples[ filename.toString() ] = sample;
    Logger::warning( " Loaded %s to sample %i.",filename.toString().c_str(), _d->samples.size() );
  }

  return true;
}

void Engine::play( vfs::Path filename, int volume)
{
  if(_d->useSound )
  {
    bool isLoading = load( filename );

    if( isLoading )
    {
      Impl::Samples::iterator i = _d->samples.find( filename.toString() );

      if( i == _d->samples.end() )
      {
        return;
      }

      if( (i->second.channel == -1 )
          || (i->second.channel >= 0 && Mix_Playing( i->second.channel ) <= 0) )
      {

        // sdl_mixer finds free channel, we then play at correct volume
        i->second.channel = Mix_PlayChannel(-1, i->second.chunk, 0);
      }

      Mix_Volume( i->second.channel,(volume*MIX_MAX_VOLUME)/256);
    }
  }
}

void Engine::stop( vfs::Path filename )
{

  Impl::Samples::iterator i = _d->samples.find( filename.toString() );

  if( i == _d->samples.end() )
  {
    return;
  }

  Mix_HaltChannel( i->second.channel );
  Mix_FreeChunk( i->second.chunk );

  _d->samples.erase( i );
}

}//end namespace audio
