#include "BaseFormula.h"

std::ostream & operator << (std::ostream & ostr, const Formula & f)
{
  f->printFormula(ostr);
  return ostr;
}

