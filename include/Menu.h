/*
  StackIT: Menu.h
  UFSCAR@2017

  Esta classe é responsável por definir o menu do jogo.
*/

#ifndef MENU_H
#define MENU_H

/*
 *	Libraries
 ***********************************************************************/
#include <iostream>
#include <string>

#include "cScreen.h"
#include <windows.h>
#include "AnimatedSprite.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

/*
 *	Classes
 ***********************************************************************/
class Menu: public Telas {

    private:
        bool playing;

        //sprite com todas as imagens
        sf::Texture fundoJogo;
        Animation fundoJogoMovimento;
        AnimatedSprite background;
        sf::Clock frameClock;

        sf::Font font;
        sf::Music sound;

        sf::Text play;
        sf::Text instrucoes;
        sf::Text back;
        sf::Text quit;

    public:
        Menu();
        virtual int Run(sf::RenderWindow &App);
};

#endif // MENU_H
