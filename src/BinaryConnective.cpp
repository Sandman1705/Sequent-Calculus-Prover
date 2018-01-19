#include "BinaryConnective.h"

bool BinaryConnective::equalTo(const Formula & f) const
{
  return f->getType() == getType() &&
    _op1->equalTo(((BinaryConnective *)f.get())->getOperand1())
    &&
    _op2->equalTo(((BinaryConnective *)f.get())->getOperand2());
}

BinaryConnective::BinaryConnective(const Formula & op1, const Formula & op2)
  :_op1(op1),
   _op2(op2)
{}

const Formula & BinaryConnective::getOperand1() const
{
  return _op1;
}

const Formula & BinaryConnective::getOperand2() const
{
  return _op2;
}

