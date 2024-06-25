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
#include "../inc/polynomial.hpp"
#include "../inc/term.hpp"


Polynomial::Polynomial()
{

}
#ifdef LIST
Polynomial::Polynomial(const std::list<Term>& terms) :
    m_terms {std::list<Term>(terms)}
{
        
}
#else
Polynomial::Polynomial(const std::vector<Term>& terms) :
    m_terms {std::vector<Term>(terms)}
{
        
}
#endif
Polynomial::Polynomial(const std::vector<std::array<double, 2>>& terms)
{
#ifndef LIST
    m_terms.reserve(terms.size());
#endif
    for (std::array<double, 2> term : terms)
    {
    #ifdef LIST
        m_terms.push_front(Term(term[0], term[1]));
    #else
        m_terms.push_back(Term(term[0], term[1]));
    #endif
    }
}
#ifdef LIST
Polynomial::Polynomial(const Polynomial& other) :
    m_terms {std::list<Term>(other.m_terms)}
{

}
#else
Polynomial::Polynomial(const Polynomial& other) :
    m_terms {std::vector<Term>(other.m_terms)}
{

}
#endif
Polynomial::Polynomial(Polynomial&& other) :
    m_terms {std::move(other.m_terms)}
{

}

void Polynomial::operator=(const Polynomial& other)
{
#ifdef LIST
    m_terms = std::list<Term>(other.m_terms);
#else
    m_terms = std::vector<Term>(other.m_terms);
#endif
}

Polynomial Polynomial::operator+(const Polynomial& other) const
{
#ifdef LIST
    Polynomial newPolynomial = Polynomial(std::list<Term>());
    std::unordered_map<double, Term*> exponentToPtr;
    exponentToPtr.reserve(m_terms.size()+other.m_terms.size());
#else
    Polynomial newPolynomial = Polynomial(std::vector<Term>());
    newPolynomial.m_terms.reserve(m_terms.size()+other.m_terms.size());
    std::unordered_map<double, size_t> exponentToIndex;
    exponentToIndex.reserve(m_terms.size()+other.m_terms.size());
#endif
    for (const Term& term : m_terms)
    {
    #ifdef LIST
        if (exponentToPtr.count(term.exponent))
        {
            exponentToPtr[term.exponent]->leadingTerm += term.leadingTerm;
        }
        else
        {
            newPolynomial.m_terms.push_front(term);
            exponentToPtr[term.exponent] = &newPolynomial.m_terms.front();
        }
    #else
        if (exponentToIndex.count(term.exponent))
        {
            int index = exponentToIndex[term.exponent];
            newPolynomial.m_terms[index].leadingTerm += term.leadingTerm;
        }
        else
        {
            newPolynomial.m_terms.push_back(term);
            exponentToIndex[term.exponent] = newPolynomial.m_terms.size()-1;
        }
    #endif
    }
    for (const Term& term : other.m_terms)
    {
    #ifdef LIST
        if (exponentToPtr.count(term.exponent))
        {
            exponentToPtr[term.exponent]->leadingTerm += term.leadingTerm;
        }
        else
        {
            newPolynomial.m_terms.push_front(term);
            exponentToPtr[term.exponent] = &newPolynomial.m_terms.front();
        }
    #else
        if (exponentToIndex.count(term.exponent))
        {
            size_t index = exponentToIndex[term.exponent];
            newPolynomial.m_terms[index].leadingTerm += term.leadingTerm;
        }
        else
        {
            newPolynomial.m_terms.push_back(term);
            exponentToIndex[term.exponent] = newPolynomial.m_terms.size()-1;
        }
    #endif
    }
    return newPolynomial;
}
Polynomial Polynomial::operator*(const Polynomial& other) const
{
#ifdef LIST
    Polynomial newPolynomial = Polynomial(std::list<Term>());
    std::unordered_map<double, Term*> exponentToPtr;
    exponentToPtr.reserve(m_terms.size()*other.m_terms.size());
#else
    Polynomial newPolynomial = Polynomial(std::vector<Term>());
    newPolynomial.m_terms.reserve(m_terms.size()*other.m_terms.size());
    std::unordered_map<double, size_t> exponentToIndex;
    exponentToIndex.reserve(m_terms.size()*other.m_terms.size());
#endif
    for (const Term& term : m_terms)
    {
        for (const Term& oTerm : other.m_terms)
        {
            Term newTerm = term.multiply(oTerm);
        
        #ifdef LIST
            if (exponentToPtr.count(newTerm.exponent))
            {
                exponentToPtr[newTerm.exponent]->leadingTerm += newTerm.leadingTerm;
            }
            else
            {
                newPolynomial.m_terms.push_front(newTerm);
                exponentToPtr[newTerm.exponent] = &newPolynomial.m_terms.front();
            }
        #else
            if (exponentToIndex.count(newTerm.exponent))
            {
                size_t index = exponentToIndex[newTerm.exponent];
                newPolynomial.m_terms[index].leadingTerm += newTerm.leadingTerm;
            }
            else
            {
                newPolynomial.m_terms.push_back(newTerm);
                exponentToIndex[newTerm.exponent] = newPolynomial.m_terms.size()-1;
            }
        #endif
        }
    }
    return newPolynomial;
}

double Polynomial::calculate(double assignedVal) const
{
    double finalNumber;
    for (const Term& term : m_terms)
    {
        double sum = 1;
        sum *= std::pow(assignedVal, term.exponent);
        sum *= term.leadingTerm;
        finalNumber += sum;
    }
    return finalNumber;
}

void Polynomial::print() const
{
    int size = 0;
    for (const Term& term : m_terms)
    {
        if (term.leadingTerm == 0)
        {
            continue;
        }
        else if (term.leadingTerm != 1)
        {
            std::cout << term.leadingTerm;
        }

        if (term.exponent != 0 && term.exponent == 1)
        {
            std::cout << "x";
        }
        else if (term.exponent != 0)
        {
            std::cout << "x^" << term.exponent;
        }

        if (size != m_terms.size()-1)
        {
            std::cout << " + ";
        }
        size++;
    }
    std::cout << std::endl;
}


void Polynomial::addTerm(const Term& term)
{
    if (term.leadingTerm == 0) 
    {
        return;
    }
    for (Term& newTerm : m_terms)
    {
        if (newTerm.canAdd(term))
        {
            newTerm.leadingTerm += term.leadingTerm;
            return;
        }
    }
#ifdef LIST
    m_terms.push_front(term);
#else
    m_terms.push_back(term);
#endif
}
