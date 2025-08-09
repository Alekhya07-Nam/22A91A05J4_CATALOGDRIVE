#include <bits/stdc++.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

long long charToDigit(char ch)
{
    if ('0' <= ch && ch <= '9')
        return ch - '0';
    if ('A' <= ch && ch <= 'Z')
        return ch - 'A' + 10;
    if ('a' <= ch && ch <= 'z')
        return ch - 'a' + 10;
    throw runtime_error("Invalid digit in value");
}

long long convertFromBase(int base, const string &encodedVal)
{
    long long number = 0;
    for (char ch : encodedVal)
    {
        long long digit = charToDigit(ch);
        if (digit >= base)
            throw runtime_error("Digit >= base");
        number = number * base + digit;
    }
    return number;
}

long long lagrangeInterpolationAtZero(const vector<long long> &xVals, const vector<long long> &yVals, int pointCount)
{
    long long constantTerm = 0;
    for (int i = 0; i < pointCount; i++)
    {
        long double term = yVals[i];
        for (int j = 0; j < pointCount; j++)
        {
            if (i != j)
            {
                term *= (-xVals[j]) / (long double)(xVals[i] - xVals[j]);
            }
        }
        constantTerm += llround(term);
    }
    return constantTerm;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream inputFile("input.json");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open input.json\n";
        return 1;
    }

    json inputData;
    inputFile >> inputData;

    int totalPoints = inputData["keys"]["n"];
    int requiredPoints = inputData["keys"]["k"];

    vector<long long> xCoordinates, yCoordinates;
    for (auto &entry : inputData.items())
    {
        if (entry.key() == "keys")
            continue;
        long long xValue = stoll(entry.key());
        int baseValue = stoi(entry.value()["base"].get<string>());
        string encodedValue = entry.value()["value"];
        long long yValue = convertFromBase(baseValue, encodedValue);
        xCoordinates.push_back(xValue);
        yCoordinates.push_back(yValue);
    }

    long long constantC = lagrangeInterpolationAtZero(xCoordinates, yCoordinates, requiredPoints);
    cout << "The value of c = " << constantC << "\n";

    return 0;
}