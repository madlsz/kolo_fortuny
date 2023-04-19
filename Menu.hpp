#pragma once

#include <iostream>

class Menu
{
    public:
        std::string members[2];
        int member_count;
        int choice;
        void get_choice();
        void print_menu();
        Menu();
};