#include "True.h"

BaseFormula::Type True::getType() const
{
  return T_TRUE;
}

void True::printFormula(std::ostream & ostr) const
{
  ostr << "TRUE";
}
