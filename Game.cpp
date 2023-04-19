#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <cassert>

#include "Game.hpp"
#include "Player.hpp"
#include "Password.hpp"
#include "Menu.hpp"

#define DEBUG true

Game::Game(int player_count)
{
    this->menu = new Menu;
    this->kolejka = 0;
    this->password = new Password(get_random_password());
    std::string names[3] = {"Bryanusz", "Jessica", "Nepomucen"};
    for(int i=player_count-1; i!=-1; i--)
    {
        this->players.push_back(new Player(names[i]));
    }
    this->suma = 0;
    this->kwota = 0;
    this->sa_spolgloski = false;
    this->proba = "";
    this->rezultat = "";
    this->wheel = new Wheel;
    this->zgadl = 0;
    this->literka = 'a';
}

Game::~Game()
{
    for(auto & player:this->players)
    {
        delete player;
    }
    // this->players.clear();
    delete this->password;
    delete this->wheel;
    delete this->menu;
}

std::string Game::get_random_password()
{
    std::vector<std::string> passwords;
    std::ifstream strum;
    strum.open("dane.txt");

    setlocale(LC_CTYPE, "Polish");

    while (!strum.eof())
    {
        std::string s;
        //strum >> s;
        getline(strum, s);
        //cout << s << endl;
        passwords.push_back(s);

    }

    strum.close();

    assert(passwords.size() > 0);
    int i = rand() % passwords.size(); // losujemy j-te haslo z przedzialu 0 ... size - 1
    //cout << hasla[j];

    std::string password = passwords[i];
    return password;
}

void Game::update_mask()
{
    for(int i=0; i<this->password->password.size(); i++)
    {
        if(this->password->password[i] == ' ')
        {
            this->mask.push_back(0);
        }
        else
        {
            this->mask.push_back(1);
        }
    }
}

void Game::print_mask()
{
    for(int i=0; i<this->password->password.size(); i++)
    {
        if(this->mask[i] == 1)
        {
            std::cout << ".";
        }
        else
        {
            std::cout << this->password->password[i];
        }
    }
}

void Game::text_players()
{
    for(int i=0; i<this->players.size(); i++)
    {
        if(i==this->kolejka)
        {
            std::cout << ">";
        }
        else
        {
           std::cout << " "; 
        }
        std::cout << this->players[i]->name << "\t" << this->players[i]->kasa << "\n";
    }
}

void Game::play()
{
    Menu menu;

    do
    {
        if(DEBUG)
        {
            std::cout << "Haslo to: ";
            this->password->print_password();
            std::cout << "\n";
        }

        this->update_mask();
        this->print_mask();
        std::cout << "\n";

        for(int i=0; i<this->password->password.length(); i++)
        {
            if ((!this->password->jest_samogloska(this->password->password[i])) && (this->mask[i]))
            {
                sa_spolgloski = true;
                break;
            }
        }
        if (sa_spolgloski)
        {
            std::cout << " -- Spolgloski sa --\n";
        }
        
        this->text_players();
        std::cout << "\n";

        this->menu->print_menu();
        this->menu->get_choice();

        if(this->menu->choice == 1)
        {
            std::cout << "Podaj haslo: ";
            std::getline(std::cin >> std::ws, proba);
            for(auto & c : proba)
            {
                c = toupper(c);
            }

            if(this->password->password == proba)
            {
                std::cout << std::endl << " !!!!!!!!!! =======   WYGRANA ========== !!!!!!!!!!!!!" << std::endl;
                this->players[this->kolejka]->portfel += this->players[this->kolejka]->kasa;
                break;
            }
            else
            {
                this->kolejka = (this->kolejka + 1) % 3;
                this->suma = 1;
                std::cout << std::endl << " !!!!!!!!!! =======   ZLE ========== !!!!!!!!!!!!!" << std::endl;
                std::cout << std::endl << "=================================================" << std::endl;
                continue;
            }
        }

        int wheel_spin_result = wheel->spin();
        if(wheel_spin_result == 0)
        {
            this->rezultat = "Strata kolejki";
        }
        if(wheel_spin_result == -1)
        {
            this->rezultat = "Bankrut";
        }

        if (rezultat != "")
        {
            std::cout << rezultat << "\n";
        }
        else
        {
            std::cout << wheel_spin_result << "\n";
            this->kwota = wheel_spin_result;
        }

        // Strata kolejki i bankrut
        if ((wheel_spin_result == 0) || (wheel_spin_result == -1))
        {
            // bankrut
            if(wheel_spin_result == -1)
            {
                this->players[this->kolejka]->kasa = 0;
            }
            this->kolejka = (this->kolejka + 1) % 3;
            this->suma = 1;
            std::cout << std::endl << "=================================================" << std::endl;
            continue;
        }

        std::cout << this->players[this->kolejka]->name <<  ": Podaj litere" << std::endl;
        std::cin >> this->literka;
        this->literka = toupper(this->literka);
        this->zgadl = 0;
        if(this->password->jest_samogloska(this->literka))
        {
            std::cout << "samogloska";
        }
        else
        {
            std::cout << "spolgloska";
        }
        std::cout << std::endl;

        for (int i = 0; i < this->password->password.size(); i++)
        {
            if ((this->password->password[i] == this->literka) && (this->mask[i]==1)) {
                this->mask[i] = 0;
                this->zgadl++;
            }
        }

        if(this->zgadl)
        {
            std::cout << "OK";
            this->players[this->kolejka]->kasa += this->kwota * this->zgadl;
            std::cout << std::endl << this->players[this->kolejka]->name << this->players[this->kolejka]->kasa;
        }
        else
        {
            std::cout << "Zle!";
            // strata kolejki
            this->kolejka = (this->kolejka + 1) % 3;
            std::cout << std::endl << "=================================================" << std::endl;
            this->suma = 1;
            continue;
        }

        std::cout << "\n";

        this->suma = 0;

        for (int i = 0; i < this->password->password.size(); i++)
        {
            this->suma += this->mask[i];
        }

        std::cout << "\n\n\n\n";
    } while (this->suma);

    std::cout << "BRAWO!";
    
}