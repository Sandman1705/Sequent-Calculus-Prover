#ifndef UNARYCONNECTIVE_H
#define UNARYCONNECTIVE_H

#include "BaseFormula.h"

/* Unarni veznik (obuhvata samo Not) */
class UnaryConnective : public BaseFormula {
protected:
  Formula _op;
public:
  UnaryConnective(const Formula & op);
  const Formula & getOperand() const;
  virtual bool equalTo(const Formula & f) const;

};

#endif // UNARYCONNECTIVE_H
