#ifndef CSCREEN_H
#define CSCREEN_H

#include <SFML/Graphics.hpp>

#include "../src/Pilha.cpp"

#define SAIR -1
#define INSTRUCAO 0
#define MENU 1
#define LEXICOGRAPHICPERMUTE 2
#define JOHNSONTROTTER 3

//classe pai que conterá todas as telas
class Telas {
    public :

    //método virtual puro, classe abstrata
    virtual int Run (sf::RenderWindow &App) = 0;

};

#endif // CSCREEN_H
