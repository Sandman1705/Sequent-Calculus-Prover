#ifndef ATOM_H
#define ATOM_H

#include "AtomicFormula.h"
#include <string>

class Atom : public AtomicFormula {
private:
  unsigned _var_num;
  std::string _var_name;
public:
  Atom(unsigned num);
  Atom(std::string name);
  unsigned getVariableNumber() const;
  std::string getVariableName() const;
  virtual void printFormula(std::ostream & ostr) const;
  virtual Type getType() const;
  virtual bool equalTo(const Formula &  f) const;
};

#endif // ATOM_H
