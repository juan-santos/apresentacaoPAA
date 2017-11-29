/*
  StackIT: Jogo.h
  UFSCAR@2017

  Esta classe é responsável por definir o jogo em si.
*/

#ifndef JOGO_H
#define JOGO_H


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

#include "AnimatedSprite.h"
#include "../src/Pilha.cpp"

#define NRO_CASAS 20
#define TAMANHO_ITEM 30

#define NUMERO_FASES 5

//itens
#define CONCRETO 0
#define GRAMA 1
#define PEDRA 2
#define AGUA 3
#define PAREDE 4
#define OBJ1 5
#define OBJ2 6
#define OBJ3 7
#define OBJ4 8
#define OBJ5 9

#define POS_INICIAL_X 30
#define POS_INICIAL_Y 30

#define SEGUIR 0
#define HORARIO 1
#define ANTIHORARIO 2
#define FUNCAO1 3
#define FUNCAO2 4
#define PEGAR 5
#define LIMPAR 6
#define EXECUTAR 7

/*
 *	Classes
 ***********************************************************************/
using namespace std;
class Jogo : public Telas {

    private:

        Pilha<int> pilha;
        Pilha<int> pilhafuncao1;
        Pilha<int> pilhafuncao2;
        sf::Sprite objeto;

        //botão
        sf::Texture controle[8];
        sf::Sprite seguir;
        sf::Sprite horario;
        sf::Sprite antihorario;
        sf::Sprite funcao1;
        sf::Sprite funcao2;
        sf::Sprite pegar;
        sf::Sprite limpar;
        sf::Sprite executar;

        //imagens com os itens/trecos
        sf::Texture itens[10];
        sf::Sprite mapa;

        //painel
        sf::Texture backgroundPainel;
        sf::Sprite painel;

        sf::Texture texture;
        Animation walkingAnimationDown;
        Animation walkingAnimationLeft;
        Animation walkingAnimationRight;
        Animation walkingAnimationUp;
        Animation* currentAnimation;

        sf::Clock frameClock;
        AnimatedSprite animatedSprite;

        float speed;
        bool noKeyWasPressed;

        int mapaAtual[NRO_CASAS][NRO_CASAS];
        int fase;
        int sentido;
        bool movimento;

        //método que redesenha o jogo durante o loop
        void desenharJogo(sf::RenderWindow &App);

        //verifica se existe uma proxima fase, chama os métodos de carregar e desenhar fases
        void avancarFase(sf::RenderWindow &App);
        //carrega a matriz da fase atual
        void carregarMapaAtual(sf::RenderWindow &App, int fase);
        //desenha a fase atual
        void desenharMapaAtual(sf::RenderWindow &App);

        //desenha todas as opções de controle
        int funcionalidadeBotao(sf::RenderWindow &App, sf::Event &event);
        void desenharOpcoesControle(sf::RenderWindow &App);

        //desenha a fila que o jogador escolheu para fazer o personagem se mover
        void desenharFilaControle(sf::RenderWindow &App);
        void desenharFilaControleF1(sf::RenderWindow &App);
        void desenharFilaControleF2(sf::RenderWindow &App);

        int descobrirX(const float x) const;
        int descobrirY(const float y) const;
        bool podeSeguir(const int x, const int y) const;
        bool ehItemMapa(const int x, const int y) const;
        bool estaNoIntervaloDoMapa(const int x, const int y) const;
        int numeroItensMapa() const;
        bool pegarItem (const int x, const int y);
        bool morre(const int x, const int y) const;

        //adiciona um controle
        void adicionarControle();

        //remove todos os controles de movimento (provisório, melhoria será remover um único item por vez)
        void removerControle();

        //executa a fila de controles, verificando o caminho e movimentando o personagem
        int executarFilaControle(sf::RenderWindow &App);
        bool observarJogador(sf::RenderWindow &App, bool movimento);
        void resetarJogador(sf::RenderWindow &App);

        bool movimentarPersonagem(sf::RenderWindow &App, Pilha<int> &pilha);
        void verificarCaminho(float x, float y) const;

        sf::Music sound;

    public:
        Jogo();
        virtual int Run(sf::RenderWindow &App);

};

#endif //JOGO_H
