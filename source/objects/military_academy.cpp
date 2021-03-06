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
// Copyright 2012-2014 Dalerank, dalerankn8@gmail.com

#include "military_academy.hpp"
#include "constants.hpp"
#include "objects_factory.hpp"

using namespace constants;

REGISTER_CLASS_IN_OVERLAYFACTORY( objects::military_academy, MilitaryAcademy)

MilitaryAcademy::MilitaryAcademy()
  : WorkingBuilding( objects::military_academy, Size(3) )
{
}
