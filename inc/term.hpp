#ifndef TERM
#define TERM

#include <iostream>

struct Term
{
    double leadingTerm;
    double exponent;

    Term();
    Term(double leadingTerm, double exponent);
    Term(const Term& other);
    Term(Term&& other);

    bool equal(const Term& other) const;

    bool canAdd(const Term& other) const;

    Term multiply(const Term& other) const;
};

#endif