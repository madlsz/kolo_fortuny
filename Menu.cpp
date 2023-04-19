#include <iostream>
#include <string>

#include "Menu.hpp"

Menu::Menu()
{
    this->members[0] = "Zgaduj haslo";
    this->members[1] = "Krecenie kolem";
    this->choice = 0;
    this->member_count = 2;
}

void Menu::get_choice()
{
    std::string choice;
    std::cin >> choice;
    if(choice.length()==1)
    {
        this->choice = std::stoi(choice);
    }
    else
    {
        this->choice = 1;
    }
}

void Menu::print_menu()
{
    for(int i=0; i<this->member_count; i++)
    {
        std::cout << i+1 << ". " << this->members[i] << "\n";
    }
}