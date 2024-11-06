#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <vector>
#include <string>

class Register {
private:
    std::vector<std::string> Reg;

public:
    Register();
    void setRegister(const int &i, const std::string &content);
    std::string at(const int &i) const;
    void displayRegister() const;
    void clear();
    ~Register();
};

#endif // REGISTER_H
