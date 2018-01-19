#ifndef IMP_H
#define IMP_H

#include "BinaryConnective.h"

class Imp : public BinaryConnective {
public:
  // Uvozimo konstruktor iz bazne klase
  using BinaryConnective::BinaryConnective;

  virtual void printFormula(std::ostream & ostr) const;
  virtual Type getType() const;
};

#endif // IMP_H
