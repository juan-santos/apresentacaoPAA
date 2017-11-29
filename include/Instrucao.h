#ifndef INSTRUCAO_H
#define INSTRUCAO_H

#include <iostream>
#include "cScreen.h"
#include <string>

#include <SFML/Graphics.hpp>
using namespace std;

class Instrucao: public Telas{

    private:

    public:
        Instrucao();
        virtual int Run(sf::RenderWindow &App);
};

#endif // INSTRUCAO_H
