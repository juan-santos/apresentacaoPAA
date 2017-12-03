#ifndef LEXICOGRAPHICPERMUTE_H
#define LEXICOGRAPHICPERMUTE_H


/*
 *	Libraries
 ***********************************************************************/
#include <iostream>
#include "cScreen.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <math.h>

#include <windows.h>
#include <fstream>

#define EXECUTAR 0
#define LIMPAR 1
#define CARTA1 2
#define CARTA2 3
#define CARTA3 4
#define CARTA4 5
#define CARTA5 6
#define CARTA6 7
#define SETA 8

#define ESQUERDA 0
#define DIREITA 1

typedef struct{
    int valor, seta, movel;
    bool pintadoMaior, pintadoMenor;
} elemento_lp;

/*
 *	Classes
 ***********************************************************************/
using namespace std;
class LexicographicPermute : public Telas {

    private:

        Pilha<int> pilha;
        sf::Sprite objeto;
        sf::Sprite movel;

        //botão
        sf::Texture controle[9];
        sf::Sprite carta1;
        sf::Sprite carta2;
        sf::Sprite carta3;
        sf::Sprite carta4;
        sf::Sprite carta5;
        sf::Sprite carta6;
        sf::Sprite limpar;
        sf::Sprite executar;

        //painel
        sf::Texture backgroundPainel;
        sf::Texture backgroundfundo;
        sf::Sprite painel;
        sf::Sprite background;

        sf::Texture texture;
        bool estaExecutando;
        bool noKeyWasPressed;

        //método que redesenha o jogo durante o loop
        void desenharJogo(sf::RenderWindow &App);

        //desenha a fase atual
        void desenharFundoPlano(sf::RenderWindow &App);

        //desenha todas as opções de controle
        int funcionalidadeBotao(sf::RenderWindow &App, sf::Event &event);
        void desenharOpcoesControle(sf::RenderWindow &App);

        //desenha a fila que o jogador escolheu para fazer o personagem se mover
        void desenharFilaControle(sf::RenderWindow &App);


        Pilha<elemento_lp> pilhaPermutacao;
        void calculaLexicographicPermute(int vetor[], int quantidade_elementos);
        void calcularPermutacoes(sf::RenderWindow &App);
        void desenharPermutacoes(sf::RenderWindow &App);

        //executa a fila de controles, verificando o caminho e movimentando o personagem
        int executarFilaControle(sf::RenderWindow &App);

    public:
        LexicographicPermute();
        virtual int Run(sf::RenderWindow &App);

};

#endif //LEXICOGRAPHICPERMUTE_H
