#ifndef AND_H
#define AND_H

#include "BinaryConnective.h"

class And : public BinaryConnective {
public:
  // Uvozimo konstruktor iz bazne klase
  using BinaryConnective::BinaryConnective;

  virtual void printFormula(std::ostream & ostr) const;
  virtual Type getType() const;

};

#endif // AND_H
