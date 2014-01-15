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
// Copyright 2012-2013 Dalerank, dalerankn8@gmail.com

#ifndef _CAESARIA_GOOD_H_INCLUDE_
#define _CAESARIA_GOOD_H_INCLUDE_

#include <string>
#include <vector>
#include <map>

class VariantList;

class Good
{
public:
  typedef enum
  {
    none=0,
    wheat, fish, meat, fruit, vegetable,
    olive, oil,
    grape, wine,
    timber, furniture,
    clay, pottery,
    iron, weapon,
    marble,
    denaries,
    goodCount
  } Type;

  virtual Type type() const { return _type; }

protected:
  Type _type;
};

class GoodStock : public Good
{
public:
  GoodStock();
  GoodStock(const Good::Type &goodType, const int maxQty, const int currentQty=0);
  ~GoodStock();

  void setType( Good::Type goodType );

  void setCapacity( const int maxQty );
  int capacity() const { return _capacity; }

  void setQty( const int qty ) { _qty = qty; }
  int qty() const { return _qty; }

  int freeQty() const;

  void push( const int qty ) { _qty += qty; }
  void pop( const int qty ) { _qty -= qty; }

  /** amount: if -1, amount=stock._currentQty */
  void append(GoodStock &stock, const int amount = -1);

  VariantList save() const;
  void load( const VariantList& options );

  bool empty() const;

protected:
  int _capacity;
  int _qty;
};
    
#endif //_CAESARIA_GOOD_H_INCLUDE_
