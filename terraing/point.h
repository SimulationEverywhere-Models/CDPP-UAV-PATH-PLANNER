#ifndef POINT_H 
#define POINT_H
/**
 * @file point.h
 * @author Keith Holman
 * @date Created: Wednesday, November 12, 2008
 * @brief Point object
 */

#include <string.h> /* for memset */

/**
 * @brief N-Dimensional Point Object
 * @tparam T    internal type for storing of coordinates
 * @tparam N    number of dimensions
 */
template< typename T, unsigned int N = 2 >
class Point
{
public:
  /**
   * @brief Default Constructor
   */
  Point();

  /**
   * @brief Constructor
   * @parma v         array of values to initialize the point object to
   */
  explicit Point( const T v[N] );

  bool operator==( const Point< T, N >& o ) const;
  bool operator!=( const Point< T, N >& o ) const;
  bool operator< ( const Point< T, N >& o ) const;
  bool operator<=( const Point< T, N >& o ) const;
  bool operator> ( const Point< T, N >& o ) const;
  bool operator>=( const Point< T, N >& o ) const;

  /**
   * @brief Returns the number of dimensions of the point object
   * @return a number representing the number of dimensions
   */
  unsigned int getDimensions() const { return N; }
  /**
   * @brief Returns a specific value in a dimension
   * @param d         dimension to retrieve value for
   * @return value    in that dimension
   */
  T get( unsigned int d ) const { return ( d < N ? _p[d] : 0 ); }
  /**
   * @brief Sets the value of only 1 dimension
   */ 
  void set( const unsigned int d, const T v )
  {
    if ( d < N ) _p[d] = v;
  }
  void set( const T v[N] );
private:
  T _p[N];
};

template< typename T, unsigned int N >
Point< T, N >::Point()
{
  memset( &_p[0], 0, N * sizeof( T ) );
}

template< typename T, unsigned int N >
Point< T, N >::Point( const T v[N] )
{
  set( v );
}
template< typename T, unsigned int N >
void Point< T, N >::set( const T v[N] )
{
  for ( unsigned int n = 0u; n < N; ++n )
  {
    _p[n] = v[n];
  }
}
template< typename T, unsigned int N >
bool Point< T, N >::operator==( const Point< T, N >& o ) const
{
  bool result = true;
  for ( unsigned int n = 0u; n < N; ++n )
  {
    if ( _p[n] != o._p[n] ) { result = false; break; }
  }
  return result;
}
template< typename T, unsigned int N >
bool Point< T, N >::operator!=( const Point< T, N >& o ) const
{
  return !operator==( o );
}
template< typename T, unsigned int N >
bool Point< T, N >::operator< ( const Point< T, N >& o ) const
{
  bool result = false;
  for ( unsigned int n = 0u; n < N; ++n )
  { 
    if ( _p[n] < o._p[n] )
    {
      result = true;
      break;
    }
    else if ( _p[n] > o._p[n] ) break;
  }
  return result;
}
template< typename T, unsigned int N >
bool Point< T, N >::operator<=( const Point< T, N >& o ) const
{
  return ( operator<( o ) || operator==( o ) );
}
template< typename T, unsigned int N >
bool Point< T, N >::operator> ( const Point< T, N >& o ) const
{
  return !operator<=( o );
}
template< typename T, unsigned int N >
bool Point< T, N >::operator>=( const Point< T, N >& o ) const
{
  return ( operator>( o ) || operator==( o ) );
}
#endif // ifndef POINT_H