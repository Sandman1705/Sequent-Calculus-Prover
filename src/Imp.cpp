#include "Imp.h"

#include "True.h"
#include "Not.h"
#include "Or.h"

BaseFormula::Type Imp::getType() const
{
  return T_IMP;
}

void Imp::printFormula(std::ostream & ostr) const
{
  ostr << "(" << _op1 <<  " => " << _op2 << ")";
}

