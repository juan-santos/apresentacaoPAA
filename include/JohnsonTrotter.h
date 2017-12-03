#ifndef JOHNSONTROTTER_H
#define JOHNSONTROTTER_H

#include <iostream>
#include "cScreen.h"
#include <string>

#include <SFML/Graphics.hpp>
using namespace std;

class JohnsonTrotter: public Telas{

    private:

    public:
        JohnsonTrotter();
        virtual int Run(sf::RenderWindow &App);
};

#endif // JOHNSONTROTTER_H
