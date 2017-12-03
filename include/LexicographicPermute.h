#ifndef LEXICOGRAPHICPERMUTE_H
#define LEXICOGRAPHICPERMUTE_H

#include <iostream>
#include "cScreen.h"
#include <string>

#include <SFML/Graphics.hpp>
using namespace std;

class LexicographicPermute: public Telas{

    private:

    public:
        LexicographicPermute();
        virtual int Run(sf::RenderWindow &App);
};

#endif // LEXICOGRAPHICPERMUTE_H
