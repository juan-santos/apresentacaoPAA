#ifndef ERRO_H
#define ERRO_H

/*
 *	Libraries
 ***********************************************************************/
#include <iostream>
#include <string>

#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
 *	Classes
 ***********************************************************************/

class Erro: public Telas {

    public:
        Erro();
        virtual int Run(sf::RenderWindow &App);
};

#endif // ERRO_H
