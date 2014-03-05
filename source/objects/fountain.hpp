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

#ifndef __CAESARIA_FOUNTAIN_INCLUDED__
#define __CAESARIA_FOUNTAIN_INCLUDED__

#include "core/position.hpp"
#include "service.hpp"

class Fountain : public ServiceBuilding
{
public:
  Fountain();

  virtual void build( PlayerCityPtr city, const TilePos& pos );
  virtual bool canBuild(PlayerCityPtr city, TilePos pos , const TilesArray& aroundTiles) const;
  virtual void deliverService();
  virtual void timeStep(const unsigned long time);
  virtual bool isNeedRoadAccess() const;
  virtual bool isActive() const;
  virtual bool haveReservoirAccess() const;
  virtual void destroy();

  virtual void load( const VariantMap& stream);
  virtual void save(VariantMap &stream) const;
private:
  bool _haveReservoirWater;
  void _initAnimation();
  int _waterIncreaseInterval;
  int _lastPicId;
};

#endif //__CAESARIA_FOUNTAIN_INCLUDED__