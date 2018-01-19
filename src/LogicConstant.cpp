#include "LogicConstant.h"

bool LogicConstant::equalTo(const Formula & f) const
{
  return f->getType() == getType();
}
