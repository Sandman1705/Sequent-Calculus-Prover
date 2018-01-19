#include "ProofTree.h"

#include "Sequent.h"
/*
ProofTree::ProofTree(Seq s, Tree l, Tree r)
    : seq(std::move(s)), left(std::move(l)), right(std::move(r))
{
}
*/
ProofTree::ProofTree(Seq s, Rule ru, Tree l, Tree r)
    : seq(std::move(s)), rule(ru), left(std::move(l)), right(std::move(r))
{
}

void ProofTree::printProofTree(std::ostream & ostr, unsigned depth) const
{
    for (unsigned i=0; i<depth; ++i)
        ostr << "\t";
    printRule(ostr);
    ostr << seq << "\n";
    if (left)
        left->printProofTree(ostr,depth+1);
    if (right)
        right->printProofTree(ostr,depth+1);
}

void ProofTree::printRule(std::ostream & ostr) const
{
    switch(rule)
    {
    case R_ASS:
        ostr << "Ax: ";
        break;
    case R_TRUE_R:
        ostr << "LT: ";
        break;
    case R_FALSE_L:
        ostr << "R~T: ";
        break;
    case R_AND_L:
        ostr << "L/\\: ";
        break;
    case R_AND_R:
        ostr << "R/\\: ";
        break;
    case R_OR_L:
        ostr << "L\\/: ";
        break;
    case R_OR_R:
        ostr << "R\\/: ";
        break;
    case R_NOT_L:
        ostr << "L~: ";
        break;
    case R_NOT_R:
        ostr << "R~: ";
        break;
    case R_IMP_L:
        ostr << "L=>: ";
        break;
    case R_IMP_R:
        ostr << "R=>: ";
        break;
    case R_THIN:
        ostr << "Thin: ";
        break;
    case R_CONT:
        ostr << "Cont: ";
        break;
    default:
        ostr << "Unknown: ";
        break;
    }


}

std::ostream & operator << (std::ostream & ostr, const ProofTree & pt)
{
  pt.printProofTree(ostr,0);
  return ostr;
}

std::ostream & operator << (std::ostream & ostr, const Tree & pt)
{
  pt->printProofTree(ostr,0);
  return ostr;
}
