/**
 * @file main.cpp
 * @author Keith Holman
 * @date Created: Tuesday, November 11, 2008
 * @brief Source file for a simple terrain generator
 */

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>

#include <string.h>
#include <stdlib.h>

#include "defaults.h"
#include "generator.h"
#include "layer.h"
#include "point.h"

/**
 * @brief Type that stores all the layers that should be generated
 */
typedef std::vector< Layer* > LayerCollection;

/**
 * @brief Function for reading rules to generate a source file
 * @param filename    path to file to read rules from
 * @param generators  collection of generators to use for each layer
 */
bool read_file( const char* const filename, LayerCollection& layers )
{
  bool result = false;
  std::ifstream in_file( filename );
  if ( in_file )
  {
    std::cout << "Reading Generation Rules From: \"" << filename << "\"" << std::endl;
    enum ReadFileConstants
    {
      BUFFER_SIZE = 1024
    };
    unsigned int layer_num = 0u;
    Layer* parent_layer = new Layer( layer_num ); // Create Parent Layer
    Layer* cur_layer = parent_layer;
    layers.push_back( parent_layer );
    char buffer[ BUFFER_SIZE ];
    unsigned int line_num = 1;
    result = true;
    while ( in_file.getline( buffer, BUFFER_SIZE ) )
    {
      char* p = buffer;
      const char* key = p;
      const char* value = 0;
      bool ignore_line = false;
      while ( p && *p && !ignore_line )
      {
        // Comment line
        char c = *p;
        switch ( c )
        {
        case '%':
          ignore_line = true;
        case '[':
          cur_layer = new Layer( ++layer_num, parent_layer );
          layers.push_back( cur_layer );
          ignore_line = true;
          break;
        case ' ':
          if ( key == p )
          {
            ++key;
          }
          else if ( value == p )
          {
            ++value;
          }
          if ( value == 0 )
          {
            *p = 0; // trim spaces from end of key
          }
          break; // ignore space characters starting a key
        case '=':
          *p = 0;
          value = p + 1;
          break;
        }
        if ( !ignore_line && !*(p+1) )
        {
          if ( !key || !value )
          {
            std::cerr << "Error: Line " << line_num << 
              ": '=' found without key and/or value." << std::endl;
            result = false;
          }
          else
          {
            cur_layer->insert( key, value );
          }
        }
        ++p;
      }
      ++line_num;
    }
    in_file.close();
  }
  else
  {
    std::cerr << "Failed to open: \"" << filename << "\"" << std::endl;
  }

  return result;
}

/**
 * @brief Object deletion functor
 *
 * Deletes objects stored on the heap
 */
template< typename T >
class FunctorDeleteObject
{
public:
  /**
   * @brief Functor for deleting objects
   * @param obj     object to delete
   */
  void operator() ( T obj ) const
  {
    delete obj;
  }
};

template< typename T >
class FunctorExecuteGenerator
{
public:
  FunctorExecuteGenerator( std::ostream* out );

  void operator() ( T obj )
  {
    const Layer& layer = (*obj);
    if ( _count != 0 ) /* Don't generator parent layer */
    {
      Generator* gen = NewGenerator( layer.find( "generator", "" ) );
      if ( gen )
      {
        gen->exec( *_out, *obj );
        delete gen;
      }
    }
    ++_count;
  }
private:
  std::ostream* _out;
  unsigned int _count;
};

template< typename T >
FunctorExecuteGenerator< T >::FunctorExecuteGenerator(
  std::ostream* out )
  : _count( 0u ), _out( out )
{
}

/**
 * @brief Application entry point
 * @param argc      number of arguments passed to the application
 * @param argv      array of arguments passed to the application
 */
int main( int argc, char** argv )
{
  int retval = EXIT_SUCCESS;
  LayerCollection layers;
  const char* out_file = 0;
  if ( argc > 1 )
  {
    read_file( argv[1], layers );
    if ( argc > 2 )
    {
      out_file = argv[2];
    }
  }

  std::ostream* out = &std::cout;
  std::ofstream ofile;
  if ( out_file && strlen( out_file ) > 0 )
    ofile.open( out_file );
  if ( ofile.is_open() ) out = &ofile;

  (*out) << std::setprecision( 4 );

  std::for_each( layers.begin(), layers.end(),
    FunctorExecuteGenerator< LayerCollection::value_type >( out ) );

  if ( ofile.is_open() )
  {
    ofile.close();
    std::cout << "Terrain file \"" << out_file << "\" generated." << std::endl;
  }

  std::for_each( layers.begin(), layers.end(),
    FunctorDeleteObject< LayerCollection::value_type >() );
  return retval;
}