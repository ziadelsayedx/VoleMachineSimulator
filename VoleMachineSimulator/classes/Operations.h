#include <iostream>
#include "Register.h"
#include "ALU.h"
#include "Memory.h"
using namespace std;
class Operation1
{
public:
  void execute(const char &R, const string &XY, Register *r, Memory *m)
  {
    r->setRegister(ALU::hexaToDec(R), m->at(ALU::hexaToDec(XY)));
  }
};
class Operation2
{
public:
  void execute(const char &R, const string &XY, Register *r)
  {
    r->setRegister(ALU::hexaToDec(R), XY);
  }
};
class Operation3
{
public:
  void execute(const char &R, const string &XY, Register *r, Memory *m)
  {
    m->setMemory(ALU::hexaToDec(XY), r->at(ALU::hexaToDec(R)));
  }
};
class Operation4
{
public:
  void execute(Register *r, const char &R, const char &S)
  {
    r->setRegister(ALU::hexaToDec(S), r->at(ALU::hexaToDec(R)));
  }
};
class Operation5
{
public:
  void execute(Register *r, const char &R, const char &S, const char &T)
  {
    string n1 = ALU::hexaToBin(r->at(ALU::hexaToDec(S)));
    string n2 = ALU::hexaToBin(r->at(ALU::hexaToDec(T)));
    string result = ALU::binToHexa(ALU::addInTwosComp(n1, n2));
    r->setRegister(ALU::hexaToDec(R), result);
  }
};
class Operation6
{
public:
  void execute(Register *r, const char &R, const char &S, const char &T)
  {
    string n1 = r->at(ALU::hexaToDec(S));
    string n2 = r->at(ALU::hexaToDec(T));
    string result = ALU::addInFloatNotation(n1, n2);
    r->setRegister(ALU::hexaToDec(R), result);
  }
};
class Operation7
{
public:
  void execute(Register *r, const char &R, const char &S, const char &T)
  {
    string n1 = r->at(ALU::hexaToDec(S));
    string n2 = r->at(ALU::hexaToDec(T));
    string result = ALU::OR(n1, n2);
    r->setRegister(ALU::hexaToDec(R), result);
  }
};
class Operation8
{
public:
  void execute(Register *r, const char &R, const char &S, const char &T)
  {
    string n1 = r->at(ALU::hexaToDec(S));
    string n2 = r->at(ALU::hexaToDec(T));
    string result = ALU::AND(n1, n2);
    r->setRegister(ALU::hexaToDec(R), result);
  }
};
class Operation9
{
public:
  void execute(Register *r, const char &R, const char &S, const char &T)
  {
    string n1 = r->at(ALU::hexaToDec(S));
    string n2 = r->at(ALU::hexaToDec(T));
    string result = ALU::XOR(n1, n2);
    r->setRegister(ALU::hexaToDec(R), result);
  }
};
class OperationA
{
public:
  void execute(Register *r, const char &R, const char &X)
  {
    int x = ALU::hexaToDec(X);
    string hexaNum = r->at(ALU::hexaToDec(R)), binNum = ALU::hexaToBin(hexaNum[0]) + ALU::hexaToBin(hexaNum[1]);
    x = x % binNum.size();
    for (int i = 0; i < x; i++)
    {
      char c = binNum.back();
      binNum.pop_back();
      binNum = c + binNum;
    }
    r->setRegister(ALU::hexaToDec(R), ALU::binToHexa(binNum.substr(0, 4)) + ALU::binToHexa(binNum.substr(4, 8)));
  }
};
class OperationB
{
public:
  void execute(const char &R, const string &XY, int &programCounter, Register *r)
  {
    if (r->at(0) == r->at(ALU::hexaToDec(R)))
    {
      programCounter = ALU::hexaToDec(XY);
    }
    else
      programCounter += 2;
  }
};
class OperationD
{
public:
  void execute(const char &R, const string &XY, int &programCounter, Register *r)
  {
    if (ALU::hexaToDec(r->at(0)) < ALU::hexaToDec(r->at(ALU::hexaToDec(R))))
    {
      programCounter = ALU::hexaToDec(XY);
    }
    else
      programCounter += 2;
  }
};