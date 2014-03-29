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

#include "bow_arrow.hpp"
#include "core/gettext.hpp"
#include "city/city.hpp"
#include "game/resourcegroup.hpp"
#include "gfx/tilemap.hpp"
#include "core/foreach.hpp"

using namespace constants;

BowArrowPtr BowArrow::create(PlayerCityPtr city)
{
  BowArrowPtr ret( new BowArrow( city ) );
  ret->drop();

  return ret;
}

void BowArrow::_onTarget()
{
  WalkerList walkers = _city()->getWalkers( walker::any, dstPos() );
  foreach( w, walkers )
  {
    (*w)->updateHealth( -3 );
    (*w)->acceptAction( Walker::acFight, startPos() );
  }
}

const char* BowArrow::rcGroup() const {  return ResourceGroup::sprites; }
int BowArrow::rcStartIndex() const { return 130; }

BowArrow::BowArrow(PlayerCityPtr city) : ThrowingWeapon( city )
{
  _setType( walker::bow_arrow );

  setName( _("##bow_arrow##") );
}
