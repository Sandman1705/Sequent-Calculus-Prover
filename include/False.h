#ifndef FALSE_H
#define FALSE_H

#include "LogicConstant.h"

class False : public LogicConstant {

public:
  virtual void printFormula(std::ostream & ostr) const;
  virtual Type getType() const;
};

#endif // FALSE_H
