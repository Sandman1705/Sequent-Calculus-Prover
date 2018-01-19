#ifndef IFF_H
#define IFF_H

#include "BinaryConnective.h"

class Iff : public BinaryConnective {
public:
  // Uvozimo konstruktor iz bazne klase
  using BinaryConnective::BinaryConnective;

  virtual void printFormula(std::ostream & ostr) const;
  virtual Type getType() const;

};

#endif // IFF_H
