#include "Machine.h"

Machine::Machine()
    : programCounter(0), runall(false), op('\0'), R('\0'), S('\0'), T('\0'), currInstruction(""), XY(""),
      reg(new Register()), mem(new Memory()), cu(new CU()) {}

void Machine::outputFile()
{
    ofstream memoryFile("MemoryFile.txt");
    for (int i = 0; i < 255; i++)
        memoryFile << mem->at(i) << '\n';
    memoryFile << mem->at(255);

    ofstream regFile("RegFile.txt");
    for (int i = 0; i < 15; i++)
        regFile << reg->at(i) << '\n';
    regFile << reg->at(15);
}

bool Machine::reachEnd()
{
    return programCounter > maxPC;
}

bool Machine::foundHalt()
{
    return op == 'C';
}

bool Machine::failed()
{
    return (op == '0') || (programCounter % 2);
}

void Machine::fetch()
{
    currInstruction = mem->at(programCounter) + mem->at(programCounter + 1);
}

void Machine::decode()
{
    op = currInstruction[0];
    R = currInstruction[1];
    S = currInstruction[2];
    T = currInstruction[3];
    XY = currInstruction.substr(2, 4);
}

void Machine::execute()
{
    switch (op)
    {
    case '1':
        cu->op1.execute(R, XY, reg, mem);
        break;
    case '2':
        cu->op2.execute(R, XY, reg);
        break;
    case '3':
        cu->op3.execute(R, XY, reg, mem);
        break;
    case '4':
        R = currInstruction[2];
        S = currInstruction[3];
        cu->op4.execute(reg, R, S);
        break;
    case '5':
        cu->op5.execute(reg, R, S, T);
        break;
    case '6':
        cu->op6.execute(reg, R, S, T);
        break;
    case '7':
        cu->op7.execute(reg, R, S, T);
        break;
    case '8':
        cu->op8.execute(reg, R, S, T);
        break;
    case '9':
        cu->op9.execute(reg, R, S, T);
        break;
    case 'A':
        cu->opA.execute(reg, R, T);
        break;
    case 'B':
        cu->opB.execute(R, XY, programCounter, reg);
        break;
    case 'D':
        cu->opD.execute(R, XY, programCounter, reg);
        break;
    default:
        break;
    }

    if (!(op == 'B' || op == 'D'))
        programCounter += 2;
}

bool Machine::end()
{
    if (foundHalt())
    {
        cout << "Program found halt.\n";
        return true;
    }
    else if (reachEnd())
    {
        cout << "Program reached end.\n";
        return true;
    }
    else if (failed() || !ALU::validInst(currInstruction))
    {
        cout << "Error! Not a valid Op.\n";
        return true;
    }
    return false;
}

void Machine::displayStatus()
{
    cout << "Reg           |memory           " << endl;
    for (int i = 0; i < 255; i++)
    {
        if (i < 16)
            cout << reg->at(i);
        else
            cout << "  " ;
        cout << "            |";
        string bin = ALU::hexaToBin(mem->at(i));
        while(bin.size() < 8) bin = '0' + bin;
        cout << mem->at(i) << " " << bin << "      " << ALU::hexaToDec(mem->at(i)) + '0' << endl;
    }
}

void Machine::start()
{
    if (instructions == nullptr)
    {
        instructions = new Instructions();
        instructions->loadInstructions();
        mem->setMemory(instructions->getInput());
        cout << ".--------------------." << endl;
        programCounter = instructions->startPC();
    }
    cout << ".--------------------." << endl;
    runall = instructions->runAllOrOne();
    while (true)
    {
        cout << ".--------------------." << endl;
        fetch();
        cout << "PC: " << programCounter << endl;
        cout << "Current instruction: " << currInstruction << endl;
        decode();
        execute();
        if (end())
            break;
        if (runall)
            continue;
        if (instructions->displayStatus())
            this->displayStatus();
        cout << ".--------------------." << endl;
        runall = instructions->runAllOrOne();
    }
    outputFile();
}

Machine::~Machine()
{
    delete instructions;
    delete mem;
    delete reg;
    delete cu;
}
