#include "Sequent.h"

#include <iostream>
#include "BaseFormula.h"
#include "ProofTree.h"
#include "UnaryConnective.h"
#include "BinaryConnective.h"
#include "Imp.h"
#include "And.h"

Sequent::Sequent(SeqList&& l, SeqList&& r)
    :   left(std::move(l)),
        right(std::move(r))
{
}

void Sequent::printSequent(std::ostream & ostr) const
{
    if (left.size()>0)
    {
        auto i = left.begin();
        ostr << *i++; //++i;
        for (auto e = left.end(); i!=e; ++i)
            ostr << ", " << *i ;
    }
    ostr << " |- ";
    if (right.size()>0)
    {
        auto j = right.begin();
        ostr << *j++;
        for (auto e = right.end(); j!=e; ++j)
            ostr << ", " << *j ;
    }
}

std::shared_ptr<ProofTree> Sequent::prove(bool ignore_structural)
{
    //Constants: false on left side
    for (auto i = left.begin(), el = left.end(); i!=el; ++i)
        if ((*i)->getType() == BaseFormula::T_FALSE)
        {
            Tree child = std::make_shared<ProofTree>(
                std::make_shared<Sequent>(SeqList{*i}),
                ProofTree::R_FALSE_L);
            if (left.size() == 1 && right.size() == 0)
                return child;
            Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                    ProofTree::R_THIN,
                                                    child);
            return base;
        }

    //Constants: true on right side
    for (auto i = right.begin(), el = right.end(); i!=el; ++i)
        if ((*i)->getType() == BaseFormula::T_TRUE)
        {
            Tree child = std::make_shared<ProofTree>(
                std::make_shared<Sequent>(SeqList{},SeqList{*i}),
                ProofTree::R_TRUE_R);
            if (left.size() == 0 && right.size() == 1)
                return child;
            Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                    ProofTree::R_THIN,
                                                    child);
            return base;
        }

    //assumption (and thinning)
    for (auto i = left.begin(), el = left.end(); i!=el; ++i)
        if ((*i)->getType() == BaseFormula::T_ATOM)
            for (auto j = right.begin(), er = right.end(); j!=er; ++j)
                if ((*i)->equalTo(*j))
                {
                    if (ignore_structural)
                        return std::make_shared<ProofTree>(shared_from_this(),
                                                            ProofTree::R_ASS);
                    Tree child = std::make_shared<ProofTree>(
                        std::make_shared<Sequent>(SeqList {*i}, SeqList {*j}),
                        ProofTree::R_ASS);
                    if (left.size() == 1 && right.size() == 1)
                        return child;
                    Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                            ProofTree::R_THIN,
                                                            child);
                    return base;
                }

    //contraction left
    if (!ignore_structural)
    for (auto i = left.begin(), el = left.end(); i!=el; ++i)
    {
        auto j = i;
        for (++j; j!=el; ++j)
            if ((*i)->equalTo(*j))
            {
                SeqList leftcopy = left;
                SeqList rightcopy = right;
                auto l = leftcopy.begin();
                std::advance(l, std::distance(left.begin(), j));

                leftcopy.erase(l);
                Seq child = std::make_shared<Sequent>(std::move(leftcopy),
                                                      std::move(rightcopy));
                Tree proof = child->prove(ignore_structural);
                if (proof)
                {
                    Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                            ProofTree::R_CONT,
                                                            proof);
                    return base;
                }
            }
    }

    //contraction right
    if (!ignore_structural)
    for (auto i = right.begin(), er = right.end(); i!=er; ++i)
    {
        auto j = i;
        for (++j; j!=er; ++j)
            if ((*i)->equalTo(*j))
            {
                SeqList leftcopy = left;
                SeqList rightcopy = right;
                auto l = rightcopy.begin();
                std::advance(l, std::distance(right.begin(), j));

                rightcopy.erase(l);
                Seq child = std::make_shared<Sequent>(std::move(leftcopy),
                                                      std::move(rightcopy));
                Tree proof = child->prove(ignore_structural);
                if (proof)
                {
                    Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                            ProofTree::R_CONT,
                                                            proof);
                    return base;
                }
            }
    }

    //left NOT, AND
    for (auto i = left.begin(), el = left.end(); i!=el; ++i)
        if (((*i)->getType() == BaseFormula::T_NOT) ||
            ((*i)->getType() == BaseFormula::T_AND)    )
        {
            SeqList leftcopy = left;
            SeqList rightcopy = right;
            auto j = leftcopy.begin();
            std::advance(j, std::distance(left.begin(), i));
            leftcopy.erase(j);
            ProofTree::Rule rule;

            if ((*i)->getType() == BaseFormula::T_NOT)
            {
                Formula op = ((UnaryConnective*)(*i).get())->getOperand();
                rightcopy.push_back(op);
                rule = ProofTree::R_NOT_L;
            }
            else //if ((*i)->getType() == BaseFormula::T_AND)
            {
                Formula op1 = ((BinaryConnective*)(*i).get())->getOperand1();
                Formula op2 = ((BinaryConnective*)(*i).get())->getOperand2();
                leftcopy.push_back(op1);
                leftcopy.push_back(op2);
                rule = ProofTree::R_AND_L;
            }

            Seq child = std::make_shared<Sequent>(std::move(leftcopy),
                                                  std::move(rightcopy));
            Tree proof = child->prove(ignore_structural);
            if (proof)
            {
                Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                        rule,
                                                        proof);
                return base;
            }
        }

    //right NOT, OR, IMP
    for (auto i = right.begin(), er = right.end(); i!=er; ++i)
        if (((*i)->getType() == BaseFormula::T_NOT) ||
            ((*i)->getType() == BaseFormula::T_OR)  ||
            ((*i)->getType() == BaseFormula::T_IMP)    )
        {
            SeqList leftcopy = left;
            SeqList rightcopy = right;
            auto j = rightcopy.begin();
            std::advance(j, std::distance(right.begin(), i));
            rightcopy.erase(j);
            ProofTree::Rule rule;

            if ((*i)->getType() == BaseFormula::T_NOT)
            {
                Formula op = ((UnaryConnective*)(*i).get())->getOperand();
                leftcopy.push_back(op);
                rule = ProofTree::R_NOT_R;
            }
            else // if (((*i)->getType() == BaseFormula::T_OR) || ((*i)->getType() == BaseFormula::T_IMP))
            {
                Formula op1 = ((BinaryConnective*)(*i).get())->getOperand1();
                Formula op2 = ((BinaryConnective*)(*i).get())->getOperand2();
                rightcopy.push_back(op2);
                if ((*i)->getType() == BaseFormula::T_OR)
                {
                    rightcopy.push_back(op1);
                    rule = ProofTree::R_OR_R;
                }
                else //if ((*i)->getType() == BaseFormula::T_IMP)
                {
                    leftcopy.push_back(op1);
                    rule = ProofTree::R_IMP_R;
                }

            }

            Seq child = std::make_shared<Sequent>(std::move(leftcopy),
                                                  std::move(rightcopy));
            Tree proof = child->prove(ignore_structural);
            if (proof)
            {
                Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                        rule,
                                                        proof);
                return base;
            }
        }

    //left OR, IMP
    for (auto i = left.begin(), el = left.end(); i!=el; ++i)
        if (((*i)->getType() == BaseFormula::T_OR) ||
            ((*i)->getType() == BaseFormula::T_IMP) )
        {
            Formula op1 = ((BinaryConnective*)(*i).get())->getOperand1();
            Formula op2 = ((BinaryConnective*)(*i).get())->getOperand2();
            SeqList leftcopy1 = left;
            SeqList rightcopy1 = right;
            SeqList leftcopy2 = left;
            SeqList rightcopy2 = right;
            auto j1 = leftcopy1.begin();
            auto j2 = leftcopy2.begin();
            std::advance(j1, std::distance(left.begin(), i));
            std::advance(j2, std::distance(left.begin(), i));
            leftcopy1.erase(j1);
            leftcopy2.erase(j2);
            ProofTree::Rule rule;

            leftcopy2.push_back(op2);
            if ((*i)->getType() == BaseFormula::T_OR)
            {
                leftcopy1.push_back(op1);
                rule = ProofTree::R_OR_L;

            }
            else if ((*i)->getType() == BaseFormula::T_IMP)
            {
                rightcopy1.push_back(op1);
                rule = ProofTree::R_IMP_L;
            }

            Seq child_left = std::make_shared<Sequent>(std::move(leftcopy1),
                                                       std::move(rightcopy1));
            Seq child_right = std::make_shared<Sequent>(std::move(leftcopy2),
                                                        std::move(rightcopy2));
            Tree proof_left = child_left->prove(ignore_structural);
            if (proof_left)
            {
                Tree proof_right = child_right->prove(ignore_structural);
                if (proof_right)
                {
                    Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                            rule,
                                                            proof_left,
                                                            proof_right);
                    return base;
                }
            }
        }

    //right AND
    for (auto i = right.begin(), er = right.end(); i!=er; ++i)
        if ((*i)->getType() == BaseFormula::T_AND)
        {
            Formula op1 = ((BinaryConnective*)(*i).get())->getOperand1();
            Formula op2 = ((BinaryConnective*)(*i).get())->getOperand2();

            SeqList leftcopy1 = left;
            SeqList rightcopy1 = right;
            SeqList leftcopy2 = left;
            SeqList rightcopy2 = right;
            auto j1 = rightcopy1.begin();
            auto j2 = rightcopy2.begin();
            std::advance(j1, std::distance(right.begin(), i));
            std::advance(j2, std::distance(right.begin(), i));
            rightcopy1.erase(j1);
            rightcopy2.erase(j2);
            rightcopy1.push_back(op1);
            rightcopy2.push_back(op2);

            Seq con_right1 = std::make_shared<Sequent>(std::move(leftcopy1),
                                                       std::move(rightcopy1));
            Seq con_right2 = std::make_shared<Sequent>(std::move(leftcopy2),
                                                       std::move(rightcopy2));

            Tree proof_left = con_right1->prove(ignore_structural);
            if (proof_left)
            {
                Tree proof_right = con_right2->prove(ignore_structural);
                if (proof_right)
                {
                    Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                            ProofTree::R_AND_R,
                                                            proof_left,
                                                            proof_right);
                    return base;
                }
            }
        }

    //IFF right
    for (auto i = right.begin(), er = right.end(); i!=er; ++i)
        if ((*i)->getType() == BaseFormula::T_IFF)
        {
            Formula op1 = ((BinaryConnective*)(*i).get())->getOperand1();
            Formula op2 = ((BinaryConnective*)(*i).get())->getOperand2();

            SeqList leftcopy = left;
            SeqList rightcopy = right;
            auto j = rightcopy.begin();
            std::advance(j, std::distance(right.begin(), i));
            rightcopy.erase(j);
            rightcopy.push_back(std::make_shared<And>
                (std::make_shared<Imp>(op1,op2),
                 std::make_shared<Imp>(op2,op1)));

            Seq child = std::make_shared<Sequent>(std::move(leftcopy),
                                                  std::move(rightcopy));

            Tree proof = child->prove(ignore_structural);
            if (proof)
            {
                Tree base = std::make_shared<ProofTree>(shared_from_this(),
                                                        ProofTree::R_IFF_R,
                                                        proof);
                return base;
            }
        }

    //fail
    return nullptr;
}


std::ostream & operator << (std::ostream & ostr, const Sequent & s)
{
    s.printSequent(ostr);
    return ostr;
}


std::ostream & operator << (std::ostream & ostr, const Seq & s)
{
    s->printSequent(ostr);
    return ostr;
}

