#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "ALU.h"  

using namespace std;

class Instructions
{
private:
    vector<string> instructions;
    bool loadFile;
    bool displayEechOp;

    void pushInst(const string &inst);
    void loadFromFileOrConsole();
    void loadFromConsole();
    void loadFromFile();

public:
    Instructions();
    Instructions(const vector<string> &inst);
    int startPC();
    void loadInstructions();
    void displayInst() const;
    bool displayStatus() const;
    bool runAllOrOne() const;
    int size() const;
    string at(const int &i) const;
    bool empty() const;
    vector<string> getInput() const;
    void setInstructions(const vector<string> &inst);

    ~Instructions();
};

#endif // INSTRUCTIONS_H
