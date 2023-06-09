#ifndef GENERATOR_H
#define GENERATOR_H
/**
 * @file generator.h 
 * @author Keith Holman 
 * @date Created: Wednesday, November 12, 2008
 * @brief Defines a layer generator
 */

#include <ostream>
#include "point.h"
class Layer;

class Generator
{
public:
  Generator( const char* const name );
  virtual ~Generator();

  const char* const getName() const { return _name; }

  virtual void exec( std::ostream& out, const Layer& layer ) const = 0;

private:
  const char* const _name;
};


class GeneratorRandom : public Generator
{
public:
  GeneratorRandom();
  virtual ~GeneratorRandom();

  virtual void exec( std::ostream& out, const Layer& layer ) const;
};

class GeneratorHills : public Generator
{
public:
  GeneratorHills();
  virtual ~GeneratorHills();

  virtual void exec( std::ostream& out, const Layer& layer ) const;
};

class GeneratorBorder : public Generator
{
public:
  GeneratorBorder();
  virtual ~GeneratorBorder();

  virtual void exec( std::ostream& out, const Layer& layer ) const;
};

Generator* NewGenerator( const std::string& generator );

#endif // ifndef GENERATOR_H