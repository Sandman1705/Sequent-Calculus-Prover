#ifndef NOT_H
#define NOT_H

#include "UnaryConnective.h"

class Not : public UnaryConnective {
public:

  // Uvozimo konstruktor iz bazne klase
  using UnaryConnective::UnaryConnective;

  virtual void printFormula(std::ostream & ostr) const;
  virtual Type getType() const;

};

#endif // NOT_H
