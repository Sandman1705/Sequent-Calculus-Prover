#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>

#include "OptionParser.h"
#include "BaseFormula.h"
#include "AtomicFormula.h"
#include "LogicConstant.h"
#include "True.h"
#include "False.h"
#include "Atom.h"
#include "UnaryConnective.h"
#include "Not.h"
#include "BinaryConnective.h"
#include "And.h"
#include "Or.h"
#include "Imp.h"
#include "Iff.h"

#include "Sequent.h"
#include "ProofTree.h"

extern int yyparse();
extern Formula parsed_formula;
extern Seq parsed_sequent;

int main(int argc, char **argv)
{
    OptionParser input(argc, argv);
    //parameters
    bool continuous = false;
    bool ignore_syntax_error = false;
    bool ignore_structural = false;

    if(input.cmdOptionExists("-i") || input.cmdOptionExists("--ignore-structural"))
    {
        //must precede option "--example" which uses it
        ignore_structural = true;
    }

    if(input.cmdOptionExists("-e") || input.cmdOptionExists("--example"))
    {
        Formula p0 = std::make_shared<Atom>("p");
        Formula p1 = std::make_shared<Atom>("q");

        Formula fx0 = std::make_shared<Or>(p0,p1);
        Formula fx1 = std::make_shared<Not>(fx0);
        Formula fx2 = std::make_shared<Not>(p0);
        Formula fx3 = std::make_shared<Not>(p1);
        Formula fx4 = std::make_shared<And>(fx2,fx3);
        Formula fx5 = std::make_shared<Imp>(fx1,fx4);
        Seq sx0 = std::make_shared<Sequent>(SeqList{},SeqList{fx5});

        std::cout << "EXAMPLE" << std::endl;
        std::cout << sx0 << std::endl;

        Tree proofx0 = (*sx0).prove(ignore_structural);
        std::cout << "ProofTree print:" << std::endl;
        if (proofx0== nullptr)
            std::cout << "no proof" << std::endl;
        else
            std::cout << proofx0 << std::endl;
        return 0;
    }

    if(input.cmdOptionExists("-h") || input.cmdOptionExists("--help"))
    {
        std::cout << "Input format:\n"
            << " NOT               : ~\n"
            << " AND               : &\n"
            << " OR                : |\n"
            << " IMP               : =>\n"
            << " IFF               : <=>\n"
            << " TRUE              : true\n"
            << " FALSE             : false\n"
            << " ATOM              : string (letters and digits only)\n"
            << " formula separator : ,\n"
            << " TURNSTILE         : :\n"
            << " end of sequent    : ;"
            << "Example      : ~(a|b), c&d : ~a&~b;\n"
            << "Gives result : (~(a \\/ b)), (c /\\ d) |- ((~a) /\\ (~b))\n"
            << "Sequent can be in format:\n"
            << "\tF : G\n"
            << "\tF :  \t(left side only)\n"
            << "\t    G\t(right side only)\n"
            << "where F and G are list of formulas separated by comma (,)"
            << std::endl;
        return 0;
    }

    if(input.cmdOptionExists("-c") || input.cmdOptionExists("--continuous"))
    {
        continuous = true;
    }

    if(input.cmdOptionExists("-ci") || input.cmdOptionExists("--continuous-ignore-syntax"))
    {
        continuous = true;
        ignore_syntax_error = true;
    }

    int err;
    do
    {
        //std::cout << "Input sequent:" << std::endl;
        err = yyparse();
        //std::cout << "DONE PARSING" << std::endl;
        //std::cout << "err: " << err << std::endl;

        if(parsed_sequent.get() != 0)
        {
            std::cout << parsed_sequent << std::endl;
            Tree proofx1 = (*parsed_sequent).prove(ignore_structural);
            std::cout << "ProofTree print:" << std::endl;
            if (proofx1== nullptr)
                std::cout << "\nno proof" << std::endl;
            else
                std::cout << proofx1 << std::endl;
            parsed_sequent = nullptr;
        }
        else
            std::cout << '\n';
    } while (continuous && (!err || ignore_syntax_error));

    return 0;
}
