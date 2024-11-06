#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <string>

class Memory {
private:
    std::vector<std::string> Mem;

public:
    Memory();
    void setMemory(const int &i, const std::string &content);
    void setMemory(const std::vector<std::string> &memory);
    std::string at(const int &i) const;
    void displayMemory() const;
    void clear();
    ~Memory();
};

#endif // MEMORY_H
