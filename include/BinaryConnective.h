#ifndef BINARYCONNECTIVE_H
#define BINARYCONNECTIVE_H

#include "BaseFormula.h"

/* Binarni veznik (And, Or, Imp i Iff) */
class BinaryConnective : public BaseFormula {
protected:
  Formula _op1;
  Formula _op2;
public:
  BinaryConnective(const Formula & op1, const Formula & op2);
  const Formula & getOperand1() const;
  const Formula & getOperand2() const;
  virtual bool equalTo(const Formula & f) const;

};

#endif // BINARYCONNECTIVE_H
