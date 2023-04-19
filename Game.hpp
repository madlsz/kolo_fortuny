#pragma once

#include <iostream>
#include <vector>

#include "Player.hpp"
#include "Password.hpp"
#include "Wheel.hpp"
#include "Menu.hpp"

class Game
{
    public:
        Menu * menu;
        // std::vector<int> kolo;
        std::string rezultat;
        std::string proba;
        int kolejka;
        int suma;
        int kwota;
        int zgadl;
        char literka;
        bool sa_spolgloski;
        void print_mask();
        std::vector<Player*> players;
        std::string get_random_password();
        Password * password;
        std::vector<int> mask;
        void update_mask();
        Game(int player_count);
        ~Game();
        void play();
        void text_players();
        Wheel * wheel;
};