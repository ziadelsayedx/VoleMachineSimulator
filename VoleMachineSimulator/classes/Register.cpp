#include "Register.h"

Register::Register() {
    for (int i = 0; i < 16; i++)
        Reg.push_back("00");
}

void Register::setRegister(const int &i, const std::string &content) {
    Reg[i] = content;
    if (Reg[i].size() ==1) Reg[i] = "0" + Reg[i];
    if (Reg[i].size() == 0) Reg[i] = "00";
}

std::string Register::at(const int &i) const {
    return Reg[i];
}

void Register::displayRegister() const {
    for (int i = 0; i < 16; i++) {
        std::cout << "Reg[" << i << "] = " << Reg[i] << std::endl;
    }
}

void Register::clear() {
    for (int i = 0; i < 16; i++)
        Reg[i] = "00";
}

Register::~Register() {}
