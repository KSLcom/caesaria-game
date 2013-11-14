// This file is part of openCaesar3.
//
// openCaesar3 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// openCaesar3 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with openCaesar3.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __OPENCAESAR3_GFX_PREDEFINITIONS_H_INCLUDED__
#define __OPENCAESAR3_GFX_PREDEFINITIONS_H_INCLUDED__

#include "core/smartptr.hpp"
#include "core/predefinitions.hpp"

#include <list>
#include <vector>

PREDEFINE_CLASS_SMARTPOINTER_LIST(TileOverlay,List)

class Tile;
class Picture;
typedef std::list< const Tile* > ConstTilemapWay;
typedef std::list< Tile* > TilemapWay;
typedef std::list< Tile* > TilemapArea;
typedef std::list< Tile* > TilemapTiles;
typedef std::list< const Tile* > ConstTilemapTiles;
typedef std::list< const Tile* > ConstTilemapArea;

#endif //__OPENCAESAR3_GFX_PREDEFINITIONS_H_INCLUDED__