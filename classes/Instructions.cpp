#include "Instructions.h"

Instructions::Instructions() : loadFile(false) {}

Instructions::Instructions(const vector<string> &inst) : loadFile(false), instructions(inst) {}

int Instructions::startPC()
{
    int PC;
    cout << "Enter the PC in DEC: ";
    cin >> PC;
    if (PC > -1 && PC < 256) return PC;
    return startPC();
}

void Instructions::pushInst(const string &inst)
{
    instructions.push_back(inst.substr(0, 2));
    instructions.push_back(inst.substr(2, 4));
}

void Instructions::loadFromFileOrConsole()
{
    string choice;
    cout << "1- Execute instructions from file: " << '\n';
    cout << "2- Execute instructions from console: " << '\n';
    while (!(choice == "1" || choice == "2"))
    {
        cout << "Enter choice 1/2: ";
        getline(cin, choice);
    }
    loadFile = (choice == "1");
}

void Instructions::loadFromConsole()
{
    string inst;
    cout << "Enter Instruction/end: ";
    getline(cin, inst);
    stringstream IS(inst);
    string i;
    while (IS >> i)
    {
        if (i == "end")
            return;
        if (ALU::validInst(i))
            pushInst(i);
    }
    loadFromConsole();
}

void Instructions::loadFromFile()
{
    string filename, inst;
    cout << "Enter filename: ";
    cin >> filename;
    ifstream _file(filename);
    while (getline(_file, inst))
    {
        stringstream IS(inst);
        string i;
        while (IS >> i)
            if (ALU::validInst(i))
                pushInst(i);
    }
}

void Instructions::loadInstructions()
{
    loadFromFileOrConsole();
    cout << ".--------------------." << endl;
    if (loadFile)
        loadFromFile();
    else
        loadFromConsole();
}

void Instructions::displayInst() const
{
    for (const auto &s : instructions)
        cout << s << ' ';
    cout << endl;
}

bool Instructions::displayStatus() const
{
    cout << "Display memory and register y/n: ";
    string choice;
    cin >> choice;
    return (choice == "y");
}

bool Instructions::runAllOrOne() const
{
    cout << "1: run all instructions" << endl;
    cout << "2: run one step" << endl;
    cout << "Enter choice 1/2: ";
    string choice;
    cin >> choice;
    return (choice == "1");
}

int Instructions::size() const
{
    return instructions.size();
}

string Instructions::at(const int &i) const
{
    return instructions[i];
}

bool Instructions::empty() const
{
    return instructions.empty();
}

vector<string> Instructions::getInput() const
{
    return instructions;
}

void Instructions::setInstructions(const vector<string> &inst)
{
    instructions = inst;
}

Instructions::~Instructions() {}
