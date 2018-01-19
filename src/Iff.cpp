#include "Iff.h"

#include "True.h"
#include "Not.h"
#include "And.h"
#include "Or.h"
#include "Imp.h"

BaseFormula::Type Iff::getType() const
{
  return T_IFF;
}

void Iff::printFormula(std::ostream & ostr) const
{
    ostr << "(" << _op1 << " <=> " << _op2 << ")";
}
