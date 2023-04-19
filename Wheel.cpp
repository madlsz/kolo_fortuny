#include <random>
// #include <iostream>

#include "Wheel.hpp"

Wheel::Wheel()
{
    int kolo[] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };
    for(int i=0; i<16; i++)
    {
        this->wheel.push_back(kolo[i]);
    }
}

int Wheel::spin()
{   
    return this->wheel[rand() % this->wheel.size()];
}