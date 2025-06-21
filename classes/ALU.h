#ifndef ALU_H
#define ALU_H

#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class ALU
{
public:
    static int binToDecInt(string bin);
    static double binToDecFloat(string bin);
    static string decToBinInt(int num);
    static string decToBinFloat(double frac);
    static double opera(string s);
    static string decToBin(const long long &x);
    static long long binToDec(const string &binNum);
    static string decToHexa(const long long &x);
    static string hexaToBin(const char &x);
    static string hexaToBin(const string &num);
    static string binToHexa(const string &binNum);
    static string addInTwosComp(string num1, string num2);
    static bool ODD(const int &PC);
    static bool validHexa(const string &content);
    static bool validHexa(const char &hx);
    static bool validOp(const char &c);
    static long long hexaToDec(const string &hx);
    static long long hexaToDec(const char &hx);
    static bool validInst(const string &inst);
    static string addInFloatNotation(const string &n1, const string &n2);
    static std::string XOR(const std::string &n1, const std::string &n2);
    static std::string AND(const std::string &n1, const std::string &n2);
    static std::string OR(const std::string &n1, const std::string &n2);
};

#endif // ALU_H
