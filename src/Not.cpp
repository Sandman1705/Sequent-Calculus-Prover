#include "Not.h"
#include "True.h"
#include "False.h"
#include "And.h"
#include "Or.h"
#include "Imp.h"
#include "Iff.h"

BaseFormula::Type Not::getType() const
{
  return T_NOT;
}

void Not::printFormula(std::ostream & ostr) const
{
  ostr << "(~" << _op << ")";
}
