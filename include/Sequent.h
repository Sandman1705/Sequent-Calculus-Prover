#ifndef SEQUENT_H
#define SEQUENT_H

#include <list>
#include "BaseFormula.h"

class Sequent;
typedef std::shared_ptr<Sequent> Seq;
typedef std::list<Formula> SeqList;
class ProofTree;

class Sequent : public std::enable_shared_from_this<Sequent>
{
public:
    Sequent(SeqList&& l = SeqList(),
            SeqList&& r = SeqList());

    std::shared_ptr<ProofTree> prove(bool ignore_structural = false);

    void printSequent(std::ostream & ostr) const;

protected:
    SeqList left;
    SeqList right;
};

std::ostream & operator << (std::ostream & ostr, const Sequent & s);
std::ostream & operator << (std::ostream & ostr, const Seq & s);

#endif // SEQUENT_H
