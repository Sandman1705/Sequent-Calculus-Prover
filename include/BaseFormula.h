#ifndef BASEFORMULA_H
#define BASEFORMULA_H

#include <iostream>
#include <memory>

/* Deklaracija osnovne klase */
class BaseFormula;

/* Tip podatka koji predstavlja "rucku" za baratanje formulama
   (deljeni pokazivac na cvor u sintaksnom stablu). NAPOMENA:
   Deljeni pokazivaci se, nakon konstrukcije, sintaksno koriste
   na isti nacin kao i obicni pokazivaci (dostupni su operatori
   *, ->, kao i metoda get() kojom se dobija obican pokazivac
   koji je sadrzan u tom deljenom pokazivacu).
   Za vise informacija o koriscenju deljenih pokazivaca, videti:
   http://www.cplusplus.com/reference/memory/shared_ptr/ */
typedef std::shared_ptr<BaseFormula> Formula;

/* Apstraktna klasa za predstavljanje formula */
class BaseFormula : public std::enable_shared_from_this<BaseFormula> {

public:
  /* Tip formule (tj. vodeceg veznika formule) */
  enum Type { T_TRUE, T_FALSE, T_ATOM, T_NOT, T_AND, T_OR, T_IMP, T_IFF };

  virtual void printFormula(std::ostream & ostr) const = 0;
  virtual Type getType() const = 0;
  virtual bool equalTo(const Formula & f) const = 0;
};

std::ostream & operator << (std::ostream & ostr, const Formula & f);


#endif // BASEFORMULA_H
