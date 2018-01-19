#ifndef OR_H
#define OR_H

#include "BinaryConnective.h"

class Or : public BinaryConnective {
public:
  // Uvozimo konstruktor iz bazne klase
  using BinaryConnective::BinaryConnective;

  virtual void printFormula(std::ostream & ostr) const;
  virtual Type getType() const;
};
#endif // OR_H
