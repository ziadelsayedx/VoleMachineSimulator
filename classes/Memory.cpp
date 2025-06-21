#include "Memory.h"

Memory::Memory()
{
    for (int i = 0; i < 256; i++)
        Mem.push_back("00");
}

void Memory::setMemory(const int &i, const std::string &content)
{
    Mem[i] = content;
    if (Mem[i].size() == 1)
        Mem[i] = "0" + Mem[i];
}

void Memory::setMemory(const std::vector<std::string> &memory)
{
    for (int i = 0; i < memory.size(); i++)
        Mem[i] = memory[i];
}

std::string Memory::at(const int &i) const
{
    return Mem[i];
}

void Memory::displayMemory() const
{
    for (int i = 0; i < 256; i++)
    {
        std::cout << "Mem[" << i << "] = " << Mem[i] << std::endl;
    }
}

void Memory::clear()
{
    for (int i = 0; i < 256; i++)
        Mem[i] = "00";
}

Memory::~Memory() {}
