/*
*	Libraries
***********************************************************************/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>

#include "AnimatedSprite.h"
#include "Jogo.h"
#include "Menu.h"
#include "Instrucao.h"
#include "Vitoria.h"
#include "Erro.h"
#include "JohnsonTrotter.h"
#include "LexicographicPermute.h"

#include "Lista.h"
#include "Node.h"

using namespace std;

template <class T>
void exibirLista(Lista<T> lista){
    lista.posicionarNoPrimeiro();
    Node<T> aux;

    while(lista.getProximo(aux)){
        cout << aux << endl;
    }
}

/*
 *	Main
 ***********************************************************************/
int main(int argc, char** argv) {

	srand(time(NULL));

	//vetor de ponteiros de telas
	std::vector<Telas*> listaTelas;
	int telaAtual = INSTRUCAO;

	sf::RenderWindow App(sf::VideoMode(800, 600), "Apresentação PAA");
	App.setFramerateLimit(30);

    //opcao 3
	Instrucao a;
	listaTelas.push_back(&a);

    //opcao 1
	Menu b;
	listaTelas.push_back(&b);

	//opcao 2
	Jogo c;
	listaTelas.push_back(&c);

	//opcao 4
	Vitoria d;
	listaTelas.push_back(&d);

	//opcao 5
	Erro e;
	listaTelas.push_back(&e);

	//opção Lexicographic Permute
	LexicographicPermute f;
	listaTelas.push_back(&f);

	//opção Johnson Trotter
	JohnsonTrotter g;
	listaTelas.push_back(&g);

	//Main loop
	while (telaAtual >= 0){
        telaAtual = listaTelas[telaAtual]->Run(App);
	}

	return EXIT_SUCCESS;
}
