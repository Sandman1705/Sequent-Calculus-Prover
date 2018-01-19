#ifndef LOGICCONSTANT_H
#define LOGICCONSTANT_H

#include "AtomicFormula.h"

/* Logicke konstante (True i False) */
class LogicConstant : public AtomicFormula {

public:
  virtual bool equalTo(const Formula & f) const;
};

#endif // LOGICCONSTANT_H
