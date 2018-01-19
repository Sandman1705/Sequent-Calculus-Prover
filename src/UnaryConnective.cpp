#include "UnaryConnective.h"

bool UnaryConnective::equalTo(const Formula & f) const
{
  return f->getType() == getType() &&
    _op->equalTo(((UnaryConnective *)f.get())->getOperand());
}

UnaryConnective::UnaryConnective(const Formula & op)
  :_op(op)
{}

const Formula & UnaryConnective::getOperand() const
{
  return _op;
}
