#ifndef LAYER_H
#define LAYER_H
/**
 * @file layer.h
 * @author Keith Holman
 * @date Created: Wednesday, November 12, 2008
 * @brief Defines layer object for obtaining settings for generating a layer
 */

#include <map>
#include <string>

#include "defaults.h"

class Layer
{
public:
  explicit Layer( unsigned int z, const Layer* parent = 0 );
  Layer( unsigned int z, unsigned int c, Value min, Value max );

  std::string find( const char* const key,
                    const char* const default_value ) const;

  unsigned int getCount() const;
  Value getDefault() const;
  unsigned int getIndex() const;
  Value getMin() const;
  Value getMax() const;
  unsigned int getX() const;
  unsigned int getY() const;


  void insert( const std::string& key, const std::string& value );
private:
  typedef std::map< std::string, std::string > ValueMap;


  double getDouble( const char* const key,
                    double default_value ) const;
  unsigned int getUInt( const char* const key,
                        unsigned int default_value ) const;
private:
  unsigned int _z;
  ValueMap _values;
  const Layer* _parent;

  static const char* const KEY_COUNT;
  static const char* const KEY_MIN;
  static const char* const KEY_MAX;
};

#endif // ifndef LAYER_H