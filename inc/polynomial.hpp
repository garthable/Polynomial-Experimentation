#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <vector>
#include <array>
#include <list>
#include <string>
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "../inc/utility.hpp"
#include "term.hpp"

class Polynomial
{
public:
    Polynomial();
#ifdef LIST
    Polynomial(const std::list<Term>& terms);
#else
    Polynomial(const std::vector<Term>& terms);
#endif
    Polynomial(const std::vector<std::array<double, 2>>& terms);
    Polynomial(const Polynomial& other);
    Polynomial(Polynomial&& other);

    void operator=(const Polynomial& other);

    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;

    double calculate(double assignedVal) const;
 
    void print() const;

private:
    void addTerm(const Term& term);

#ifdef LIST
    std::list<Term> m_terms;
#else
    std::vector<Term> m_terms;
#endif
};

#endif