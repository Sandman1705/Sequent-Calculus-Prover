#include "Atom.h"

Atom::Atom(unsigned num)
  : _var_num(num)
{}

Atom::Atom(std::string name)
  : _var_name(name)
{}

BaseFormula::Type Atom::getType() const
{
  return T_ATOM;
}

void Atom::printFormula(std::ostream & ostr) const
{
  //ostr << "p_" << _var_num;
  ostr << _var_name;
}

bool Atom::equalTo(const Formula & f) const
{
  return f->getType() == T_ATOM &&
    //((Atom *)f.get())->getVariableNumber() == _var_num;
    ((Atom *)f.get())->getVariableName() == _var_name;
}

unsigned Atom::getVariableNumber() const
{
  return _var_num;
}

std::string Atom::getVariableName() const
{
  return _var_name;
}
