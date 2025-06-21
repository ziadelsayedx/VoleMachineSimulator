#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include <fstream>
#include <iostream>
#include "Instructions.h"
#include "Register.h"
#include "Memory.h"
#include "CU.h"
#include "ALU.h"

using namespace std;

class Machine
{
private:
    const int maxPC = 255;
    int programCounter;
    bool runall;
    char op, R, S, T;
    string currInstruction, XY;

    Instructions *instructions = nullptr;
    Register *reg = nullptr;
    Memory *mem = nullptr;
    CU *cu = nullptr;

    void outputFile();
    bool reachEnd();
    bool foundHalt();
    bool failed();
    void fetch();
    void decode();
    void execute();
    bool end();
    void displayStatus();
public:
    Machine();
    void start();
    ~Machine();
};

#endif // MACHINE_H
