#include "ALU.h"

int ALU::binToDecInt(string bin)
{
    int decimalValue = 0;
    int base = 1;
    for (int i = bin.length() - 1; i >= 0; i--)
    {
        if (bin[i] == '1')
        {
            decimalValue += base;
        }
        base *= 2;
    }

    return decimalValue;
}
double ALU::binToDecFloat(string bin)
{
    double decimalValue = 0;
    int base = 2;
    for (int i = 1; i <= bin.length(); i++)
    {
        if (bin[i - 1] == '1')
        {
            decimalValue += pow(base, -i);
        }
    }
    return decimalValue;
}
string ALU::decToBinInt(int num)
{
    string binary = "";
    if (num == 0)
        return "0";
    while (num > 0)
    {
        binary = to_string(num % 2) + binary;
        num /= 2;
    }
    return binary;
}
string ALU::decToBinFloat(double frac)
{
    string binary = "";
    while (frac > 0)
    {
        frac *= 2;
        if (frac >= 1)
        {
            binary += "1";
            frac -= 1;
        }
        else
        {
            binary += "0";
        }
        if (binary.length() > 32)
            break; // Limit
    }
    return binary;
}
double ALU::opera(string s)
{
    int E, S, bias = 4, shiftCount;
    S = (s[0] == '1' ? 1 : 0); // signed 1 (-), 0 (+)
    string EE = s.substr(1, 3), M = s.substr(4, 8), MFloat = "", MInt = "";
    E = binToDecInt(EE);
    shiftCount = E - bias;
    if (shiftCount > 0)
    {
        MInt = M.substr(0, shiftCount);
        MFloat = M.substr(shiftCount, 4);
    }
    else
    {
        while (shiftCount++)
            MFloat += "0";
        MFloat += M;
    }
    int mInt = 0;
    double mFloat = 0, res;
    if (MInt.length() > 0)
    {
        mInt = binToDecInt(MInt);
    }
    if (MFloat.length() > 0)
    {
        mFloat = binToDecFloat(MFloat);
    }
    return pow(-1, S) * (mInt + mFloat);
}

string ALU::decToBin(const long long &x)
{
    if (x == 0)
        return "";
    return decToBin(x / 2) + (to_string(x % 2));
}

long long ALU::binToDec(const string &binNum)
{
    long long answer = 0;
    int power = 0;
    for (int i = binNum.size() - 1; i >= 0; i--)
    {
        answer += (binNum[i] - '0') * pow(2, power++);
    }
    return answer;
}

string ALU::decToHexa(const long long &x)
{
    if (x == 0)
        return "";
    int curr = (x % 16);
    string currChar;
    if (curr > 9)
        currChar = (curr % 10) + 'A';
    else
        currChar = to_string(curr);
    return decToHexa(x / 16) + currChar;
}

string ALU::hexaToBin(const char &x)
{
    string r = decToBin(hexaToDec(x));
    while (r.size() < 4)
        r = '0' + r;
    return r;
}

string ALU::hexaToBin(const string &num)
{
    return decToBin(hexaToDec(num));
}

string ALU::binToHexa(const string &binNum)
{
    return decToHexa(binToDec(binNum));
}

string ALU::addInTwosComp(string num1, string num2)
{
    while (num1.size() < num2.size())
        num1 = "0" + num1;
    while (num2.size() < num1.size())
        num2 = "0" + num2;
    string result = "";
    int carry = 0;
    for (int i = num1.size() - 1; i >= 0; i--)
    {
        int curr = ((num1[i] - '0') + (num2[i] - '0') + carry);
        result.push_back((curr % 2) + '0');
        carry = (curr > 1);
    }
    if (carry)
        result.push_back('1');
    reverse(result.begin(), result.end());
    if (binToDec(result) > 255)
        result.pop_back();
    return result;
}

bool ALU::ODD(const int &PC)
{
    return (PC % 2);
}

bool ALU::validHexa(const string &content)
{
    for (auto &c : content)
        if (!validHexa(c))
            return false;
    return true;
}

bool ALU::validHexa(const char &hx)
{
    return (hx >= '0' && hx <= '9') || (hx >= 'A' && hx <= 'F');
}

bool ALU::validOp(const char &c)
{
    return (c >= '1' && c <= '9') || (c >= 'A' & c <= 'D');
}

long long ALU::hexaToDec(const string &hx)
{
    long long dec = 0, len = hx.size(), p = 0, curr;
    for (int i = len - 1; i >= 0; i--)
    {
        if (hx[i] < 'A')
            curr = hx[i] - '0';
        else
            curr = hx[i] - 'A' + 10;
        dec += (curr * pow(16, p++));
    }
    return dec;
}

long long ALU::hexaToDec(const char &hx)
{
    return (hx >= '0' && hx <= '9') ? (hx - '0') : (hx - 'A' + 10);
}

bool ALU::validInst(const string &inst)
{
    if (inst == "0000" || inst == "C000")
        return true;
    if (inst.size() == 4)
        if (ALU::validOp(inst[0]) && ALU::validHexa(inst.substr(1, 4)))
            return true;
    return false;
}
std::string ALU::XOR(const std::string &n1, const std::string &n2)
{
    return decToHexa(hexaToDec(n1) ^ hexaToDec(n2));
}

std::string ALU::AND(const std::string &n1, const std::string &n2)
{
    return decToHexa(hexaToDec(n1) & hexaToDec(n2));
}

std::string ALU::OR(const std::string &n1, const std::string &n2)
{
    return decToHexa(hexaToDec(n1) | hexaToDec(n2));
}

string ALU::addInFloatNotation(const string &n1, const string &n2)
{
    string binn1, binn2;
    double decn1, decn2, dec;
    int sign = 0;
    binn1 = hexaToBin(n1);
    binn2 = hexaToBin(n2);
    decn1 = opera(binn1);
    decn2 = opera(binn2);
    dec = decn1 + decn2;
    if (dec < 0)
    {
        sign = 1, dec *= -1;
    }
    int intPart = (int)dec;
    dec -= intPart;
    string binInt = "", binFloat = "", binAns;
    if (intPart != 0)
        binInt = decToBinInt(intPart);
    if (dec != 0)
        binFloat = decToBinFloat(dec);
    binAns = binInt + binFloat;
    int Expon; 
    if (binInt.length())
        Expon = binInt.length() + 4; 
    else
    { //
        int pos = binAns.find('1');
        Expon = -pos + 4;
    }
    string expl = (sign == 1 ? "1" : "0");
    string ex = decToBinInt(Expon); 
    if (ex.length() <= 3)
    { //
        string tst = "";
        int sz = ex.length();
        while (sz < 3)
        {
            tst += "0";
            sz++;
        }
        expl += tst + decToBinInt(Expon);
    }
    else
        cout << "there is overflow in Exponent (more than 3 bit), please enter a valid number!\n";
    if (binInt.length() == 0)
    {
        string ss = binAns.substr(binAns.find('1'), binAns.length());
        while (ss.length() < 4)
        {
            ss += "0";
        }
        binAns = ss;
    }
    expl += binAns.substr(0, 4);
    string ans = binToHexa(expl.substr(0, 4)) + binToHexa(expl.substr(4, 8));
    return ans;
}
