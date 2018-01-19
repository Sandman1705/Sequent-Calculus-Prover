#include "Or.h"
#include "True.h"

BaseFormula::Type Or::getType() const
{
  return T_OR;
}

void Or::printFormula(std::ostream & ostr) const
{
  ostr << "(" << _op1 << " \\/ " << _op2 << ")";
}

