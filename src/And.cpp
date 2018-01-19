#include "And.h"

BaseFormula::Type And::getType() const
{
  return T_AND;
}

void And::printFormula(std::ostream & ostr) const
{
  ostr << "(" << _op1 <<  " /\\ " << _op2 << ")";
}

