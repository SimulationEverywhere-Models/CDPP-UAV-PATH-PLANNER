/**
 * @file generator.cpp
 * @author Keith Holman
 * @date Created: Wednesday, November 12, 2008
 * @brief Defines support terrain generators
 */

#include "generator.h"
#include "defaults.h"
#include "layer.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <math.h>
#include <time.h>

typedef Point< unsigned int, 3u > Point3D;

void OutputPoint(
                  std::ostream& out, const Layer& layer,
                  const Point3D&  pnt, Value val )
{
  if ( val != layer.getDefault() )
  {
    out << "(";
    for ( unsigned int n = 0u; n < pnt.getDimensions(); ++n )
    {
      if ( n > 0u ) out << ",";
      out << pnt.get(n);
    }
    if ( val < layer.getMin() )
      val = layer.getMin();
    if ( val > layer.getMax() )
      val = layer.getMax();
    out << ") = " << val << std::endl;
  }
}


Generator::Generator(const char *const name)
: _name( name )
{
}

Generator::~Generator()
{
}


GeneratorRandom::GeneratorRandom()
: Generator( "Random" )
{
}

GeneratorRandom::~GeneratorRandom()
{
}



void GeneratorRandom::exec(std::ostream &out, const Layer &layer) const
{
  unsigned int n = layer.getCount();
  unsigned int z = layer.getIndex();
  Value rand_min = layer.getMin();
  Value rand_max = layer.getMax();
  
  srand( (unsigned int)time(NULL) );
  for ( unsigned int i = 0; i < n; ++i )
  {
    unsigned int x = rand() % layer.getX();
    unsigned int y = rand() % layer.getY();
    unsigned int d[] = { x, y, z };
    Value value = rand_min;
    if ( rand_min != rand_max )
    {
      value = rand() % static_cast< unsigned int>( rand_max - rand_min )
        + rand_min;
    }
    OutputPoint( out, layer, Point3D( d ), value );
  }
}

GeneratorHills::GeneratorHills()
: Generator( "Hills" )
{
}

GeneratorHills::~GeneratorHills()
{
}

void GeneratorHills::exec(std::ostream &out, const Layer &layer) const
{
  typedef std::map< Point3D, Value > HillMap;
  HillMap hills;
  srand( (unsigned int)time(NULL) );
  const unsigned int n = layer.getCount();
  const unsigned int max_x = layer.getX();
  const unsigned int max_y = layer.getY();
  const unsigned int z = layer.getIndex();
  const Value val_min = layer.getMin();
  const Value val_max = layer.getMax();
  for ( unsigned int i = 0; i < n; ++i )
  {
    unsigned int d[] = { rand() % max_x, rand() % max_y, z };
    Value value = rand() % (unsigned int)( val_max - val_min ) + val_min;
    Point3D point( d );
    hills.insert( HillMap::value_type( point, value ) );
  }
  for ( unsigned int x = 0u; x < max_x; ++x )
  {
    for ( unsigned int y = 0u; y < max_y; ++y )
    {
      unsigned int d[] = { x, y, z };
      Point3D pnt( d );
      HillMap::const_iterator it_find = hills.find( pnt );
      Value value = 0.0;
      if ( it_find != hills.end() )
      {
        value = it_find->second; 
      }
      else
      {
        /* Determine how much influence any surrounding hills have */
        HillMap::const_iterator it_cur = hills.begin();
        HillMap::const_iterator it_end = hills.end();
        while ( it_cur != it_end )
        {
          const Point3D& pnt = it_cur->first;
          Value dist = (Value)sqrt(
            pow((double)(x) - pnt.get( 0 ), 2) + 
            pow((double)(y) - pnt.get( 1 ), 2) );
          if ( dist < it_cur->second )
          {
            value += (it_cur->second - dist);            
          }
          ++it_cur;
        }
      }
      OutputPoint( out, layer, pnt, value );
    }
  }
}

GeneratorBorder::GeneratorBorder()
: Generator( "Border" )
{
}

GeneratorBorder::~GeneratorBorder()
{
}

void GeneratorBorder::exec( std::ostream& out, const Layer& layer ) const
{
  const unsigned int max_x = layer.getX();
  const unsigned int max_y = layer.getY();
  const unsigned int z = layer.getIndex();
  const Value value = layer.getMax();
  for ( unsigned int x = 0u; x < max_x; ++x )
  {
    if ( x == 0u || x == (max_x - 1u) )
    {
      for ( unsigned int y = 0u; y < max_y; ++y )
      {
        unsigned int d[] = { x, y, z };
        Point3D pnt( d );
        OutputPoint( out, layer, pnt, value );
      }
    }
    else
    {
      unsigned int y_vals[] = { 0u, max_y - 1u };
      for ( unsigned int y = 0u; y < 2u; ++y )
      {
        unsigned int d[] = { x, y_vals[y], z };
        Point3D pnt( d );
        OutputPoint( out, layer, pnt, value );
      }
    }
  }
}

template< typename T >
class FunctorToLower
{
public:
  void operator() ( const T& c )
  {
    _result.push_back( tolower( c ) );
  }

  operator std::string ()
  {
    return _result;
  }

private:
  std::string _result;
};

Generator* NewGenerator( const std::string& generator )
{
  Generator* result = 0;
  std::string lc_gen = std::for_each( generator.begin(), generator.end(), 
    FunctorToLower< std::string::value_type >() );

  if ( lc_gen.compare( "border" ) == 0 )
  {
    result = new GeneratorBorder();
  }
  else if ( lc_gen.compare( "hills" ) == 0 )
  {
    result = new GeneratorHills();
  }
  else
  {
    result = new GeneratorRandom();
  }
  return result;
}

