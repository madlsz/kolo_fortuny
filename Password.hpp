#pragma once

#include <iostream>

class Password
{
    public:
        std::string password;
        Password(std::string password);
        bool jest_samogloska(char c);
        void print_password();
};