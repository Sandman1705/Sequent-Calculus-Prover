#include "False.h"

BaseFormula::Type False::getType() const
{
  return T_FALSE;
}

void False::printFormula(std::ostream & ostr) const
{
  ostr << "FALSE";
}
