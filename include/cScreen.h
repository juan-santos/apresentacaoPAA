#ifndef CSCREEN_H
#define CSCREEN_H

#include <SFML/Graphics.hpp>

#define SAIR -1
#define INSTRUCAO 0
#define MENU 1
#define GAME 2
#define VITORIA 3
#define ERRO 4

//classe pai que conterá todas as telas
class Telas {
    public :

    //método virtual puro, classe abstrata
    virtual int Run (sf::RenderWindow &App) = 0;

};

#endif // CSCREEN_H
