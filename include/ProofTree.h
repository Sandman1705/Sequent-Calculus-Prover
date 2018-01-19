#ifndef PROOFTREE_H
#define PROOFTREE_H

#include <memory>
#include "Sequent.h"

class ProofTree;
typedef std::shared_ptr<ProofTree> Tree;

class ProofTree
{
public:
    enum Rule { R_ASS, R_TRUE_R, R_FALSE_L, R_AND_L, R_AND_R, R_OR_L, R_OR_R,
                R_NOT_L, R_NOT_R, R_IMP_L, R_IMP_R, R_THIN, R_CONT,
                R_IFF_R, R_IFF_L };

    //ProofTree(Seq s, Tree l = nullptr, Tree r = nullptr);
    ProofTree(Seq s, Rule ru, Tree l = nullptr, Tree r = nullptr);

    void printProofTree(std::ostream & ostr, unsigned depth) const;
    void printRule(std::ostream & ostr) const;

protected:
    Seq seq;
    Rule rule;
    Tree left;
    Tree right;
};

std::ostream & operator << (std::ostream & ostr, const ProofTree & pt);
std::ostream & operator << (std::ostream & ostr, const Tree & pt);

#endif // PROOFTREE_H
