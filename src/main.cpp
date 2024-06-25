#include "../inc/polynomial.hpp"
#include <cassert>

#ifdef TIMETEST
    #include "../inc/timer.hpp"
#endif

#ifdef MEMORYTEST
    #include "../inc/memtrack.hpp"
#endif

#include <iostream>
#include <memory>
#include <fstream>
#include <filesystem>

std::vector<std::vector<std::array<double, 2>>> generateValues(int seed, int step, int amount)
{
    std::vector<std::vector<std::array<double, 2>>> returnVal;
    srand(seed);
    for (int i = 0; i < amount; i++)
    {
        returnVal.push_back(std::vector<std::array<double, 2>>());
        for (int j = 0; j < i*step; j++)
        {
            int r1 = rand() + 1;
            double lead = static_cast<double>(r1)/1000;
            int r2 = rand() + 1;
            double exponent = static_cast<double>(r2)/1000;

            returnVal[i].push_back(std::array<double, 2>({lead, exponent}));
        }
    }
    return returnVal;
}

std::vector<Polynomial> generatePolynomials(std::vector<std::vector<std::array<double, 2>>> vals)
{
    std::vector<Polynomial> polynomials;
    for (const auto& terms : vals)
    {
        polynomials.push_back(Polynomial(terms));
    }
    return polynomials;
}


int main(int argc, char** argv)
{
#ifdef TEST 
    std::vector<std::array<double, 2>> a1 = {{1.0, 2.0}, {1.0, 3.0}, {2.0, 1.0}};
    std::vector<std::array<double, 2>> a2 = {{3.0, 3.0}, {2.0, 2.0}, {1.0, 1.0}};
    Polynomial p1 = Polynomial(a1);
    Polynomial p2 = Polynomial(a2);
    p1.print();
    p2.print();
    (p1 + p2).print();
    (p1 * p2).print();
    _print(p1.calculate(10.0));
    _print(p2.calculate(10.0));
    return 0;
#endif
    if (argc < 2)
    {
        throw std::runtime_error("Include filename!");
    }
    if (std::filesystem::exists(argv[1]))
    {
        return 0;
    }
    std::ofstream file = std::ofstream(argv[1]);
    if (!file.is_open())
    {
        throw std::runtime_error("File failed to open!");
    }

#ifdef GENTEST
    std::vector<std::vector<std::array<double, 2>>> genVals = generateValues(10, 10, 500);
#elif PROCTEST
    std::vector<Polynomial> polys = generatePolynomials(generateValues(10, 10, 500));
#else
    std::vector<Polynomial> polys1 = generatePolynomials(generateValues(10, 10, 500));
    std::vector<Polynomial> polys2 = generatePolynomials(generateValues(500, 10, 500));
#endif

#ifdef TIMETEST
    double time = 0;
    file << "Term Amount" << "," << "Time (ms)" << std::endl;
#elif MEMORYTEST
    size_t memory = 0;
    file << "Term Amount" << "," << "Peak Memory (b)" << std::endl;
#endif
    srand(10);
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            {
            #ifdef TIMETEST
                time = 0;
                Timer t = Timer(time);
            #elif MEMORYTEST
                memory = 0;
                MemTrack m = MemTrack(memory);
            #endif

            #ifdef GENTEST
                Polynomial p = Polynomial(genVals[i]);
            #elif PROCTEST
                double v = polys[i].calculate(10.0);
            #elif ADDTEST
                Polynomial p = polys1[i] + polys2[i];
            #elif MULTTEST
                Polynomial p = polys1[i] * polys2[i];
            #endif
            }
        #ifdef TIMETEST
            file << i*10 << "," << time << std::endl;
        #elif MEMORYTEST
            file << i*10 << "," << memory << std::endl;
        #endif
        }
    }
}