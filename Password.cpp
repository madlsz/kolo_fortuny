#include <iostream>

#include "Password.hpp"

Password::Password(std::string password)
{
    this->password = password;
}

bool Password::jest_samogloska(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y')
        return 1;
    else
        return 0;
}

void Password::print_password()
{
    std::cout << this->password;
}