#include "polynomial.cpp"
#include "timer.cpp"
#include <iostream>
#include <memory>
#include <fstream>

#define ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define VARSIZE 1
#define UNIQUE_DATA_POINTS 1000
#define RERUN_AMOUNT 100

double g_memoryAllocs = 0;

void* operator new(size_t size)
{
    g_memoryAllocs += static_cast<double>(size)/1000.0;
    return malloc(size);
}

std::string genPolynomial(int n, std::string vars, int seed, int max)
{
    srand(seed);
    std::ostringstream returnVal;
    for (int i = 0; i < n; i++)
    {
        returnVal << rand() % max;
        for (const char& c : vars)
        {
            returnVal << c << "^" << rand() % max;
        }
        returnVal << "+";
    }
    return returnVal.str().substr(0, returnVal.str().size()-1);
}

struct InputData
{
    int termCount;
    std::string varCount;
    InputData(int termCount, std::string varCount) :
        termCount {termCount},
        varCount {varCount}
    {

    }
};

std::vector<InputData> createInputData(int termIncrement, int startTermCount, int endTermCount)
{
    std::vector<InputData> returnVal;

    for (int termAmount = startTermCount; termAmount < endTermCount; termAmount += termIncrement)
    {
        std::string vars = ALPHABET;
        returnVal.push_back(InputData(termAmount, vars.substr(0, VARSIZE)));
    }
    return returnVal;
}

int main()
{
    Polynomial<1> polynomial = Polynomial<1>("x^2 + x + 5"); 
    Polynomial<1> polynomial1 = Polynomial<1>("x"); 
    (polynomial1 * polynomial).print();
    return 1;
    std::vector<InputData> inputData = createInputData(10, 0, 500);
    _print(inputData.size());
    std::fstream file = std::fstream("output.csv");
    file << "Average Time (ms)," << "Average Memory (kb)," << "Term Count," << "Variable Count" << std::endl;

    for (InputData _inputData : inputData)
    {
        std::vector<std::string> stringPoly;
        for (int i = 0; i < UNIQUE_DATA_POINTS; i++)
        {
            stringPoly.push_back(genPolynomial(_inputData.termCount, _inputData.varCount, i, 1000000));
        }
        g_memoryAllocs = 0;
        double totalTime = 0;
        {
            Timer t = Timer(totalTime);
            for (int i = 0; i < RERUN_AMOUNT; i++)
            {
                for (const std::string& poly : stringPoly)
                {
                    Polynomial<VARSIZE> polynomial = Polynomial<VARSIZE>(poly);
                }
            }
        }
        double averageTime = totalTime / UNIQUE_DATA_POINTS*RERUN_AMOUNT;
        double averageMem = g_memoryAllocs / UNIQUE_DATA_POINTS*RERUN_AMOUNT;
        file << averageTime << "," << averageMem << "," << _inputData.termCount << "," << _inputData.varCount.size() << std::endl;
    }
    _print("done!");
}