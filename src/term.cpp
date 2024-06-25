#include <iostream>

#include "../inc/utility.hpp"
#include "../inc/term.hpp"

Term::Term() :
    leadingTerm {1},
    exponent {0}
{

}
Term::Term(double leadingTerm, double exponent) :
    leadingTerm {leadingTerm},
    exponent {exponent}
{

}
Term::Term(const Term& other) :
    leadingTerm {other.leadingTerm},
    exponent {other.exponent}
{

}
Term::Term(Term&& other) :
    leadingTerm {std::move(other.leadingTerm)},
    exponent {std::move(other.exponent)}
{
    
}

bool Term::equal(const Term& other) const
{
    return leadingTerm == other.leadingTerm && exponent == other.exponent;
}

bool Term::canAdd(const Term& other) const
{
    return exponent == other.exponent;
}

Term Term::multiply(const Term& other) const
{
    Term newTerm = Term();
    newTerm.leadingTerm = leadingTerm * other.leadingTerm;
    newTerm.exponent = exponent + other.exponent;
    return newTerm;
}