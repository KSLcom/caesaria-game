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

#include <cstdio>

#include "infobox_colloseum.hpp"
#include "gfx/tile.hpp"
#include "objects/constants.hpp"
#include "objects/colosseum.hpp"
#include "label.hpp"
#include "core/gettext.hpp"
#include "game/gamedate.hpp"

using namespace constants;

namespace gui
{

InfoboxColosseum::InfoboxColosseum(Widget *parent, const Tile &tile)
  : InfoboxConstruction( parent, Rect( 0, 0, 470, 300), Rect( 16, 145, 470 - 16, 145 + 100 ) )
{
  ColosseumPtr coloseum = ptr_cast<Colosseum>(tile.overlay());
  setConstruction( ptr_cast<Construction>( coloseum ) );
  setTitle( _( MetaDataHolder::getPrettyName( building::colloseum ) ) );

  _updateWorkersLabel( Point( 40, 150), 542, coloseum->maxWorkers(), coloseum->numberWorkers() );
  
  if( coloseum->isNeedGladiators() )
  {
    new Label( this, Rect( 35, 190, width() - 35, 190 + 20 ), _("##colloseum_haveno_gladiatorpit##") );
  }
  else
  {
    std::string text = _("##colloseum_haveno_animal_bouts##");
    if( coloseum->isShowLionBattles() )
    {
      DateTime lastAnimalBoutDate = coloseum->getLastAnimalBoutDate();
      text = StringHelper::format( 0xff, "%s %d %s", "##colloseum_animal_contest_runs##", lastAnimalBoutDate.getDaysToDate( GameDate::current() ), "##days##" );
    }
    new Label( this, Rect( 35, 200, width() - 35, 200 + 20 ), text );

    text = _("##colloseum_haveno_gladiator_bouts##");
    if( coloseum->isShowGladiatorBattles() )
    {
      DateTime lastGlBoutDate = coloseum->getLastGladiatorBoutDate();
      text = StringHelper::format( 0xff, "%s %d %s", "##colloseum_gladiator_contest_runs##", lastGlBoutDate.getDaysToDate( GameDate::current() ), "##days##" );
    }

    new Label( this, Rect( 35, 220, width() - 35, 220 + 20 ), text );
  }
}

InfoboxColosseum::~InfoboxColosseum() {}

}//end namespace gui
