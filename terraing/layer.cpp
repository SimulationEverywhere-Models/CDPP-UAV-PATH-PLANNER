/**
 * @file layer.cpp
 * @author Keith Holman
 * @date Created: Wednesday, November 12, 2008
 * @brief Object for storing values for a layer
 */

#include "layer.h"
#include <sstream>

const char* const Layer::KEY_COUNT = "count";
const char* const Layer::KEY_MIN = "min";
const char* const Layer::KEY_MAX = "max";

Layer::Layer( unsigned int z, const Layer* parent )
: _z( z ), _parent( parent )
{
}

Layer::Layer( unsigned int z, unsigned int c, Value min, Value max )
: _z( z ), _parent( 0 )
{
  std::ostringstream oss_count, oss_min, oss_max;
  oss_count << c;
  insert( KEY_COUNT, oss_count.str() );
  oss_min << min;
  insert( KEY_MIN, oss_min.str() );
  oss_max << max;
  insert( KEY_MAX, oss_max.str() );
}

std::string Layer::find( const char* const key,
                         const char* const default_value ) const
{
  std::string retval( default_value );
  ValueMap::const_iterator it_cur = _values.find( key );
  if ( it_cur != _values.end() ) 
  {
    retval = it_cur->second;
  }
  else if ( _parent )
  {
    retval = _parent->find( key, default_value );
  }
  return retval;
}


double Layer::getDouble( const char* const key,
                         double default_value ) const
{
  std::ostringstream oss;
  oss << default_value;
  std::string result = find( key, oss.str().c_str() );
  return atof( result.c_str() );
}

unsigned int Layer::getUInt( const char* const key,
                             unsigned int default_value ) const
{
  std::ostringstream oss;
  oss << default_value;
  std::string result = find( key, oss.str().c_str() );
  return static_cast< unsigned int >( atoi( result.c_str() ) );
}

unsigned int Layer::getCount() const
{
  return getUInt( KEY_COUNT, DEFAULT_COUNT );
}

Value Layer::getDefault() const
{
  return static_cast< Value >( getDouble( "default", DEFAULT_VALUE ) );
}

Value Layer::getMin() const
{
  return static_cast< Value >( getDouble( KEY_MIN, DEFAULT_MIN ) );
}

Value Layer::getMax() const
{
  return static_cast< Value >( getDouble( KEY_MAX, DEFAULT_MAX ) );
}

unsigned int Layer::getX() const
{
  return getUInt( "x", DEFAULT_RANGE );
}

unsigned int Layer::getY() const
{
  return getUInt( "y", DEFAULT_RANGE );
}

unsigned int Layer::getIndex() const
{
  return getUInt( "z", _z );
}

void Layer::insert( const std::string& key, const std::string& value )
{
  _values.insert( ValueMap::value_type( key, value ) );
}


