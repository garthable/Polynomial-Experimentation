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

#define _NULL -1

template<unsigned char Nm>
struct Term
{
    double leadingTerm;
    double exponents[Nm];

    Term() :
        leadingTerm {1}
    {
        for (double& exponent : exponents)
        {
            exponent = 0;
        }
    }
    Term(const Term<Nm>& other) :
        leadingTerm {other.leadingTerm}
    {
        for (int i = 0; i < Nm; i++)
        {
            exponents[i] = other.exponents[i];
        }
    }
    Term(Term<Nm>&& other) :
        leadingTerm {std::move(other.leadingTerm)}
    {
        for (int i = 0; i < Nm; i++)
        {
            exponents[i] = std::move(other.exponents[i]);
        }
    }

    bool equal(const Term<Nm>& other, const std::array<unsigned char, Nm>& selfToOther) const
    {
        if (leadingTerm != other.leadingTerm)
        {
            return false;
        }
        for (int i = 0; i < Nm; i++)
        {
            if (exponents[i] != other.exponents[selfToOther[i]])
            {
                return false;
            }
        }
        return true;
    }

    bool canAdd(const Term<Nm>& other, const std::array<unsigned char, Nm>& selfToOther) const
    {
        for (int i = 0; i < Nm; i++)
        {
            if (exponents[i] != other.exponents[selfToOther[i]])
            {
                return false;
            }
        }
        return true;
    }

    Term<Nm> multiply(const Term<Nm>& other, const std::array<unsigned char, Nm>& selfToOther) const
    {
        Term<Nm> newTerm = Term<Nm>();
        newTerm.leadingTerm = leadingTerm * other.leadingTerm;
        for (int i = 0; i < Nm; i++)
        {
            newTerm.exponents[i] = exponents[i] + other.exponents[selfToOther[i]];
        }
        return newTerm;
    }

    Term<Nm> divide(const Term<Nm>& other, const std::array<unsigned char, Nm>& selfToOther) const
    {
        Term<Nm> newTerm = Term<Nm>();
        newTerm.leadingTerm = leadingTerm / other.leadingTerm;
        for (int i = 0; i < Nm; i++)
        {
            newTerm.exponents[i] = exponents[i] - other.exponents[selfToOther[i]];
        }
        return newTerm;
    }
};

template<unsigned char Nm>
class Polynomial
{
public:
    Polynomial()
    {

    }
    Polynomial(const std::unordered_map<char, unsigned char>& varToIndex, const std::array<char, Nm>& keys, const std::list<Term<Nm>>& terms) :
        m_varToIndex {std::unordered_map<char, unsigned char>(varToIndex)},
        m_keys {std::array<char, Nm>(keys)},
        m_terms {std::list<Term<Nm>>(terms)}
    {
         
    }
    Polynomial(const std::string& polynomial)
    {
        int polynomialSize = polynomial.size()-1;
        m_terms.push_front(Term<Nm>());

        int trueNumSize = 0;
        int numSize = 0;
        unsigned char currKeyIndex = 0;
        double number = 0;
        
        for (int i = polynomialSize; i >= 0; i--)
        {
            const char& c = polynomial[i];
            switch (c)
            {
            case ' ':
                break;
            case ',':
                break;
            case '^':
                break;
            case '+':
                if (numSize == 0)
                {
                    m_terms.back().leadingTerm = 1;
                }
                else
                {
                    m_terms.back().leadingTerm = number;
                }
                number = 0;
                numSize = 0;
                trueNumSize = 0;
                m_terms.push_front(Term<Nm>());
                break;
            case '-':
                number *= -1;
                break;
            case '.':
                number /= std::pow(10, numSize);
                numSize = 0;
                break;
            CASE_DIGIT(
                number += static_cast<double>(c - '0') * std::pow(10, numSize);
                numSize++;
                trueNumSize++;
            );
            default:
                if (!m_varToIndex.count(c))
                {
                    m_keys[currKeyIndex] = c;
                    m_varToIndex[c] = currKeyIndex;
                    currKeyIndex++;
                }
                if (trueNumSize == 0)
                {
                    m_terms.back().exponents[m_varToIndex[c]] = 1;
                }
                else
                {
                    m_terms.back().exponents[m_varToIndex[c]] = number;
                }
                number = 0;
                numSize = 0;
                trueNumSize = 0;
                break;
            }
        }
        if (trueNumSize == 0)
        {
            m_terms.back().leadingTerm = 1;
        }
        else
        {
            m_terms.back().leadingTerm = number;
        }
    }
    Polynomial(const Polynomial<Nm>& other) :
        m_terms {std::list<Term<Nm>>(other.m_terms)},
        m_varToIndex {std::unordered_map<char, unsigned char>(other.m_varToIndex)},
        m_keys {std::array<char, Nm>(other.m_keys)}
    {

    }
    Polynomial(Polynomial<Nm>&& other) :
        m_terms {std::move(other.m_terms)},
        m_varToIndex {std::move(other.m_varToIndex)},
        m_keys {std::move(other.m_keys)}
    {

    }
    ~Polynomial()
    {

    }

    void operator=(const Polynomial<Nm>& other)
    {
        m_terms = std::list<Term<Nm>>(other.m_terms);
        m_varToIndex = std::unordered_map<char, unsigned char>(other.m_varToIndex);
        m_keys = std::array<char, Nm>(other.m_keys);
    }
    void operator=(const std::string& other)
    {
        *this = Polynomial<Nm>(other);
    }
    bool operator==(const Polynomial<Nm>& other)
    {
        const std::array<unsigned char, Nm> selfToOther = getSelfToOther(other);

        if (m_terms.size() != other.m_terms.size())
        {
            return false;
        }

        for (const Term<Nm>& term : m_terms)
        {
            bool equal = false;
            for (const Term<Nm>& otherTerm : other.m_terms)
            {
                if (term.equal(otherTerm, selfToOther))
                {
                    equal = true;
                    break;
                }
            }
            if (!equal)
            {
                return false;
            }
        }
        return true;
    }

    Polynomial<Nm> operator+(const Polynomial& other) const
    {
        std::array<unsigned char, Nm> selfToOther = getSelfToOther(other);
        Polynomial<Nm> newPolynomial = Polynomial<Nm>(m_varToIndex, m_keys, m_terms);
        for (const Term<Nm>& term : other.m_terms)
        {
            newPolynomial.addTerm(term, selfToOther);
        }
        return newPolynomial;
    }
    Polynomial<Nm> operator*(const Polynomial<Nm>& other) const
    {
        std::array<unsigned char, Nm> selfToOther = getSelfToOther(other);
        Polynomial<Nm> newPolynomial = Polynomial<Nm>(m_varToIndex, m_keys, std::list<Term<Nm>>());
        for (const Term<Nm>& term : m_terms)
        {
            for (const Term<Nm>& oTerm : other.m_terms)
            {
                Term<Nm> newTerm = term.multiply(oTerm, selfToOther);
                newPolynomial.addTerm(newTerm, selfToOther);
            }
        }
        return newPolynomial;
    }
    Polynomial<Nm> operator*(const double& other)
    {
        Polynomial<Nm> newPolynomial = Polynomial<Nm>(*this);
        for (Term<Nm>& term : newPolynomial.m_terms)
        {
            term.leadingTerm *= other;
        }
        return newPolynomial;
    }
    Polynomial<Nm> operator-(const Polynomial<Nm>& other) const
    {
        std::array<unsigned char, Nm> selfToOther = getSelfToOther(other);
        Polynomial<Nm> newPolynomial = Polynomial<Nm>(*this);
        for (const Term<Nm>& term : other.m_terms)
        {
            newPolynomial.subtractTerm(term, selfToOther);
        }
        return newPolynomial;
    }
    Polynomial<Nm> operator/(const double& other)
    {
        Polynomial<Nm> newPolynomial = Polynomial<Nm>(*this);
        for (Term<Nm>& term : newPolynomial.m_terms)
        {
            term.leadingTerm /= other;
        }
        return newPolynomial;
    }
    Polynomial<Nm> derivative(const char& var) const
    {
        unsigned char variable = m_varToIndex.at(var);
        Polynomial<Nm> newPolynomial = Polynomial(m_varToIndex, m_keys, std::list<Term<Nm>>());
        std::array<unsigned char, Nm> selfToOther = getSelfToOther(newPolynomial);
        for (Term<Nm> term : m_terms)
        {
            term.leadingTerm *= term.exponents[variable];
            term.exponents[variable]--;
            newPolynomial.addTerm(term, selfToOther);
        }
        return newPolynomial;
    }
    Polynomial<Nm> derivative(const char& var, const int n) const
    {
        Polynomial newPolynomial = Polynomial(*this);
        for (int i = 0; i < n; i++)
        {
            newPolynomial = newPolynomial.derivative(var);
        }
        return newPolynomial;
    }
    Polynomial<Nm> operator^(const int n) const
    {
        std::list<Term<Nm>> terms = std::list<Term<Nm>>();
        terms.push_front(Term<Nm>());
        Polynomial<Nm> newPolynomial = Polynomial<Nm>(m_varToIndex, m_keys, terms);
        Polynomial<Nm> basePolynomial = Polynomial<Nm>(*this);
        for (int i = 0; i < n; i++)
        {
            newPolynomial = basePolynomial*newPolynomial;
        }
        return newPolynomial;
    }
    Polynomial<Nm> getTaylor(const char& var, const int n, const double a) const
    {
        Polynomial<Nm> polynomialSum = Polynomial<Nm>();
        Polynomial<Nm> basePolynomial = Polynomial<Nm>(*this);
        Polynomial<Nm> multPolynomial = Polynomial<Nm>(std::to_string(var) + "-" + std::to_string(a));
        for (int i = 0; i < n; i++)
        {
            double factorialSum = 1;
            for (int j = i; j >= 0; j--)
            {
                factorialSum *= static_cast<double>(j);
            }
            polynomialSum = polynomialSum + 
            (
                (multPolynomial^i) * ((basePolynomial.derivative(var, i)(std::to_string(var) + std::to_string(a)))/factorialSum)
            );
        }
        return polynomialSum;
    }

    double calculate(const std::array<unsigned char, Nm> charOrder, std::array<double, Nm> assignedVals)
    {
        double finalNumber;
        for (const Term<Nm>& term : m_terms)
        {
            double sum = 1;
            for(int i = 0; i < Nm; i++)
            {
                sum *= std::pow(assignedVals[i], term.exponents[m_varToIndex.at(charOrder[i])]);
            }
            sum *= term.leadingTerm;
            finalNumber += sum;
        }
        return finalNumber;
    }
 
    void print() const
    {
        std::ostringstream result;
        int size = m_terms.size();
        int i;
        for (i = 0; i < size; i++)
        {
            auto termIterator = std::find(m_terms.begin(), m_terms.end(), i);
            const Term<Nm> term = *termIterator;
            if (term.leadingTerm == 0)
            {
                continue;
            }
            result << term.leadingTerm;
            for (int i = 0; i < Nm; i++)
            {
                const double& exponent = term.exponents[i];
                if (exponent == 0)
                {
                    continue;
                }
                result << m_keys[i];
                if (exponent == 1)
                {
                    continue;
                }
                result << '^' << exponent;
            }
            result << " + ";
        }
        std::cout << result.str().substr(0, result.str().size() - 3) << std::endl;
    }

    void printRaw()
    {
        std::ostringstream result;
        int size = m_terms.size();
        int i;
        for (i = 0; i < size; i++)
        {
            const Term<Nm>& term = m_terms[i];
            result << term.leadingTerm;
            for (int i = 0; i < Nm; i++)
            {
                const double& exponent = term.exponents[i];
                result << m_keys[i] << '^' << exponent;
            }
            result << " + ";
        }
        std::cout << result.str() << std::endl;
    }

    std::list<Term<Nm>> m_terms;
    std::array<char, Nm> m_keys;
    std::unordered_map<char, unsigned char> m_varToIndex;

private:
    std::array<unsigned char, Nm> getSelfToOther(const Polynomial<Nm>& other) const
    {
        std::array<unsigned char, Nm> selfToOther;

        int selfKeySize = m_keys.size();
        int otherKeySize = other.m_keys.size();
        for (int i = 0; i < selfKeySize; i++)
        {
            for (int j = 0; j < otherKeySize; j++)
            {
                if (m_keys[i] == other.m_keys[j])
                {
                    selfToOther[i] = j;
                    break;
                }
            }
        }

        return selfToOther;
    }

    void addTerm(const Term<Nm>& term, const std::array<unsigned char, Nm>& selfToOther)
    {
        if (term.leadingTerm == 0) 
        {
            return;
        }
        for (Term<Nm>& newTerm : m_terms)
        {
            if (newTerm.canAdd(term, selfToOther))
            {
                newTerm.leadingTerm += term.leadingTerm;
                return;
            }
        }
        m_terms.push_front(term);
    }

    void subtractTerm(const Term<Nm>& otherTerm, const std::array<unsigned char, Nm>& selfToOther)
    {
        for (Term<Nm>& term : m_terms)
        {
            if (term.canAdd(otherTerm, selfToOther))
            {
                term.leadingTerm -= otherTerm.leadingTerm;
                return;
            }
        }
        m_terms.push_front(otherTerm);
        m_terms.back().leadingTerm *= -1;
    }
};