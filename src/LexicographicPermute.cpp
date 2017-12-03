#include "LexicographicPermute.h"
/*procura e sinaliza os elementos móveis*/
int VerificarExisteMovelLexicographicPermute(elemento_lp * vetor_jt, int quantidade_elementos) {

    int x = 0;
    for(int i = 0; i < quantidade_elementos; i++)
    {
        if(vetor_jt[i].seta == DIREITA)
        {
            if(i != quantidade_elementos - 1)
            {
                if(vetor_jt[i].valor > vetor_jt[i + 1].valor)
                {
                    x = 1;
                    vetor_jt[i].movel = 1;
                }
                else
                    vetor_jt[i].movel = 0;
            }
            else
                vetor_jt[i].movel = 0;
        }
        else
        {
            if(i != 0)
            {
                if(vetor_jt[i - 1].valor < vetor_jt[i].valor)
                {
                    x = 1;
                    vetor_jt[i].movel = 1;
                }
                else
                    vetor_jt[i].movel = 0;
            }
            else
                vetor_jt[i].movel = 0;
        }
    }

    return x;
}

int EncontrarMaiorMovelLexicographicPermute(int q, elemento_lp * vetor) {
    int maior = -1;
    int indice;
    for(int i = 0; i < q; i++)
    {
        if(vetor[i].movel)
        {
            if(vetor[i].valor > maior)
            {
                maior = vetor[i].valor;
                indice = i;
            }
        }
    }
    return indice;
}

/****** MÉTODOS DE RESOLUÇÃO DO PROBLEMA *******/
void LexicographicPermute::calculaLexicographicPermute(int vetor[], int quantidade) {

    int ultima;
    int i;
    int j;

    elemento_lp *vetor_lp = new elemento_lp[quantidade];
    for(int i = 0; i < quantidade; i++) {
        vetor_lp[i].valor = vetor[i];
        vetor_lp[i].pintadoMaior = false;
        vetor_lp[i].pintadoMenor = false;
    }
    //pinto o maior
    vetor_lp[quantidade-1].pintadoMaior = true;

    do{

        for(int i = 0; i < quantidade; i++) {
            this->pilhaPermutacao.Insere(vetor_lp[i]);

            vetor_lp[i].pintadoMaior = false;
            vetor_lp[i].pintadoMenor = false;
        }

        /*descobre se ainda é possível permutar e acha i*/
        ultima = 1;
        for(i = quantidade - 2; i >= 0; i--)
        {
            if(vetor_lp[i].valor < vetor_lp[i + 1].valor)
            {
                ultima = 0;
                break;
            }
        }

        if(!ultima)
        {
            /*acha j*/
            for(j = quantidade - 1; j >= 0; j--) {
                if(vetor_lp[i].valor < vetor_lp[j].valor) {
                    break;
                }
            }

            /*inverte i e j*/
            int aux;
            aux = vetor_lp[i].valor;
            vetor_lp[i].valor = vetor_lp[j].valor;
            vetor_lp[i].pintadoMenor = true;

            vetor_lp[j].valor = aux;
            vetor_lp[j].pintadoMaior = true;

            /*inverte a ordem os elementos de i+1 até n*/
            int b = quantidade - 1;
            int q = quantidade - i - 1;
            int inicial = i + 1;
            int final0;

            if(q % 2){
                final0 = i + (q - 1) / 2;
            }
            else {
                final0 = i + q / 2;
            }

            for(int a = inicial; a <= final0; a++) {
                aux = vetor_lp[a].valor;
                vetor_lp[a].valor = vetor_lp[b].valor;
                vetor_lp[b--].valor = aux;
            }
        }

    } while(!ultima);
}

/****** CONSTRUTOR *******/
LexicographicPermute::LexicographicPermute() {
    this->estaExecutando = false;

    /*********** PAINEL *******************/
    if(!this->backgroundPainel.loadFromFile("bin/Release/files/images/jogo/painel.jpg")){
         std::cerr << "Error loading painel" << std::endl;
    }
    this->painel.setPosition(600, 0);
    this->painel.setTexture(this->backgroundPainel);

    /*********** FUNDO *******************/
    if(!this->backgroundfundo.loadFromFile("bin/Release/files/images/jogo/quadro.png")){
         std::cerr << "Error loading painel" << std::endl;
    }

    this->background.setPosition(0, 0);
    this->background.setTexture(this->backgroundfundo);

    /************* BOTOES ***************/
    if (!this->controle[CARTA1].loadFromFile("bin/Release/files/images/jogo/copas-as.png")
        ||!this->controle[CARTA2].loadFromFile("bin/Release/files/images/jogo/copas-02.png")
        ||!this->controle[CARTA3].loadFromFile("bin/Release/files/images/jogo/espada-06.png")
        ||!this->controle[CARTA4].loadFromFile("bin/Release/files/images/jogo/ourinhos-07.png")
        ||!this->controle[CARTA5].loadFromFile("bin/Release/files/images/jogo/paus-08.png")
        ||!this->controle[CARTA6].loadFromFile("bin/Release/files/images/jogo/copas-dama.png")
        ||!this->controle[LIMPAR].loadFromFile("bin/Release/files/images/jogo/limpar.png")
        ||!this->controle[EXECUTAR].loadFromFile("bin/Release/files/images/jogo/executar.png")
        ||!this->controle[SETA].loadFromFile("bin/Release/files/images/jogo/seta2.png")
        ){
        std::cout << "Can't find the ITEM" << std::endl;
    }

    this->carta1.setPosition(610, 30);
    this->carta1.setTexture(controle[CARTA1]);

    this->carta2.setPosition(670, 30);
    this->carta2.setTexture(controle[CARTA2]);

    this->carta3.setPosition(730, 30);
    this->carta3.setTexture(controle[CARTA3]);

    this->carta4.setPosition(610, 111 );
    this->carta4.setTexture(controle[CARTA4]);

    this->carta5.setPosition(670, 111 );
    this->carta5.setTexture(controle[CARTA5]);

    this->carta6.setPosition(730, 111 );
    this->carta6.setTexture(controle[CARTA6]);

    this->limpar.setPosition(650, 550 );
    this->limpar.setTexture(controle[LIMPAR]);

    this->executar.setPosition(720, 550 );
    this->executar.setTexture(controle[EXECUTAR]);

}

/****** EXECUTAR LOOP PRINCIPAL DO PROJETO *********/
int LexicographicPermute::Run(sf::RenderWindow &App) {
    //evento do teclado
    int executar = 0;
    sf::Event event;

    while (true){

        while (App.pollEvent( event )){

            //se a janela fechar
			if (event.type == sf::Event::Closed)
				return SAIR;

			//se alguma tecla for pressionada
			if (event.type == sf::Event::KeyPressed) {

				switch (event.key.code) {

                    //se for a tecla esc
					case sf::Keyboard::Escape:
						return MENU;
                        break;
					default:
                        break;
				}
			}

			//executo as operações necessárias com o botão
			executar = this->funcionalidadeBotao(App, event);

			//se houver algum erro ou vitória
			if(executar != LEXICOGRAPHICPERMUTE){
                return executar;
			}
        }

        App.clear();
        this->desenharOpcoesControle(App);
        this->desenharJogo(App);
        App.display();
    }

    return SAIR;
}


/****** EXECUTAR PERMUTAÇÃO *********/
 int LexicographicPermute::executarFilaControle(sf::RenderWindow &App){

    if(this->estaExecutando){
        this->calcularPermutacoes(App);
        this->estaExecutando = false;
    }

     //continuo no jogo
     return LEXICOGRAPHICPERMUTE;
 }


void LexicographicPermute::calcularPermutacoes(sf::RenderWindow &App){

    if(this->estaExecutando){
        int aux[this->pilha.getTamanho()];

        this->pilha.pilhaParaVetor(aux, this->pilha.getTamanho());
        this->pilhaPermutacao.esvaziaPilha();
        calculaLexicographicPermute(aux,this->pilha.getTamanho());
        free(aux);
    }

}

/***** BOTOES *****/
int LexicographicPermute::funcionalidadeBotao(sf::RenderWindow &App, sf::Event &event){
    int operacao = LEXICOGRAPHICPERMUTE;
        switch (event.type) {

            //se o mouse mover
            case sf::Event::MouseMoved: {

                sf::Vector2i mousePos = sf::Mouse::getPosition( App );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                if (this->carta1.getGlobalBounds().contains( mousePosF ) ) {
                    this->carta1.setColor( sf::Color( 223, 180, 31 ) );
                } else {
                    this->carta1.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->carta2.getGlobalBounds().contains( mousePosF ) ) {
                    this->carta2.setColor( sf::Color( 223, 180, 31 ) );
                } else {
                    this->carta2.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->carta3.getGlobalBounds().contains( mousePosF ) ) {
                    this->carta3.setColor( sf::Color( 223, 180, 31 ) );
                } else {
                    this->carta3.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->carta4.getGlobalBounds().contains( mousePosF ) ) {
                    this->carta4.setColor( sf::Color( 223, 180, 31 ) );
                } else {
                    this->carta4.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->carta5.getGlobalBounds().contains( mousePosF ) ) {
                    this->carta5.setColor( sf::Color( 223, 180, 31 ) );
                } else {
                    this->carta5.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->carta6.getGlobalBounds().contains( mousePosF ) ) {
                    this->carta6.setColor( sf::Color( 223, 180, 31 ) );
                } else {
                    this->carta6.setColor( sf::Color( 255, 255, 255 ) );
                }
                break;
            }

            case sf::Event::MouseButtonPressed: {

                sf::Vector2i mousePos = sf::Mouse::getPosition( App );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                if (this->carta1.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {

                            //número máximo de comandos e se não é repetido
                        if(this->pilha.getTamanho() < 4 && !this->pilha.ItemRepetido(CARTA1))
                            this->pilha.Insere(CARTA1);

                        this->pilha.ordernarPilha();
                        this->pilhaPermutacao.esvaziaPilha();
                    }
                }

                if (this->carta2.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                           //número máximo de comandos e se não é repetido
                        if(this->pilha.getTamanho() < 4 && !this->pilha.ItemRepetido(CARTA2))
                            this->pilha.Insere(CARTA2);
                        this->pilha.ordernarPilha();
                        this->pilhaPermutacao.esvaziaPilha();
                    }
                }

                if (this->carta3.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                          //número máximo de comandos e se não é repetido
                        if(this->pilha.getTamanho() < 4 && !this->pilha.ItemRepetido(CARTA3))
                            this->pilha.Insere(CARTA3);
                        this->pilha.ordernarPilha();
                        this->pilhaPermutacao.esvaziaPilha();
                    }
                }

                if (this->carta4.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                          //número máximo de comandos e se não é repetido
                        if(this->pilha.getTamanho() < 4 && !this->pilha.ItemRepetido(CARTA4))
                            this->pilha.Insere(CARTA4);
                        this->pilha.ordernarPilha();
                        this->pilhaPermutacao.esvaziaPilha();
                    }
                }

                if (this->carta5.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                           //número máximo de comandos e se não é repetido
                        if(this->pilha.getTamanho() < 4 && !this->pilha.ItemRepetido(CARTA5))
                            this->pilha.Insere(CARTA5);
                        this->pilha.ordernarPilha();
                        this->pilhaPermutacao.esvaziaPilha();
                    }
                }

                if (this->carta6.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                           //número máximo de comandos e se não é repetido
                        if(this->pilha.getTamanho() < 4 && !this->pilha.ItemRepetido(CARTA6))
                            this->pilha.Insere(CARTA6);
                        this->pilha.ordernarPilha();
                        this->pilhaPermutacao.esvaziaPilha();

                    }
                }

                if (this->limpar.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int ultimo;
                        this->pilha.Retira(ultimo);
                        this->pilhaPermutacao.esvaziaPilha();
                    }
                }

                if (this->executar.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                         std::cout << "EXECUTAR" << std::endl;
                         //retorno o resultado obtido do comando

                         this->estaExecutando = true;
                         this->executarFilaControle(App);
                    }
                }

                break;
            }
        }

        return operacao;
}

/***** DESENHAR PROGRAMA *****/
void LexicographicPermute::desenharPermutacoes(sf::RenderWindow &App){

    if(this->pilhaPermutacao.getTamanho() > 0){
        //numero de itens da pilha de permutação
        int tamanho = this->pilhaPermutacao.getTamanho();
        int nroElementosPermutados = pilha.getTamanho();

        //transformo em vetor
        elemento_lp listaPermutacao[tamanho];
        this->pilhaPermutacao.pilhaParaVetor(listaPermutacao, tamanho);

        int x = 0;
        int y = 0;
        int coluna = 0;

        for (int i = 1; i <= tamanho; i++) {

            this->objeto.setTexture(this->controle[listaPermutacao[i-1].valor]);
            this->objeto.setPosition(28+ 6*x + coluna*95, 33 + x*16 + y*135);

            //se for um elemento móvel, eu pinto o objeto de amarelo
            if(listaPermutacao[i-1].pintadoMaior){
                //amarelo
                this->objeto.setColor(sf::Color(223, 180, 31));

                this->movel.setTexture(this->controle[SETA]);
                this->movel.setPosition(6*x + coluna*95, 33 + x*16 + y*135);
            }else{
                if(listaPermutacao[i-1].pintadoMenor){
                    //amarelo
                    this->objeto.setColor(sf::Color(89, 238, 253));
                }else{
                    this->objeto.setColor(sf::Color(255, 255, 255));
                }
            }

            if((i % nroElementosPermutados) == 0){
                coluna++;
                x = 0;
            }else{
                x++;
            }

            //se passou o numero maximo de colunas
            if(coluna > 5){
                y++;
                x = 0;
                coluna = 0;
            }

            App.draw(this->objeto);
            App.draw(this->movel);
            this->objeto.setColor(sf::Color( 255, 255, 255 ));
        }
        free(listaPermutacao);
    }

}

/***** Desenho todas as cartas e opções do menu *****/
void LexicographicPermute::desenharOpcoesControle(sf::RenderWindow &App){

        //desenho os botões e cartas
        App.draw(this->carta1);
        App.draw(this->carta2);
        App.draw(this->carta3);
        App.draw(this->carta4);
        App.draw(this->carta5);
        App.draw(this->carta6);
        App.draw(this->limpar);
        App.draw(this->executar);

}

void LexicographicPermute::desenharFilaControle(sf::RenderWindow &App){
    /* pilha auxiliar para desenhar os objetos */
	Pilha<int> paux;
	int aux;

	while (!this->pilha.EstaVazia()) {
		this->pilha.Retira(aux);
		paux.Insere(aux);
	}

	int numeroElemento = 0;
	int numeroElementoY = 0;
	/* agora que paux possui pilha invertida, reinserimos os valores em pilha na ordem correta e aproveitamos para desenhar o objeto! */
	while (!paux.EstaVazia()) {
		paux.Retira(aux);

		/* inserimos o elemento de volta na stack */
		pilha.Insere(aux);

		objeto.setTexture(this->controle[aux]);
		objeto.setPosition(610 + numeroElemento * 55 + 6*numeroElementoY , 350 + numeroElementoY * 20);

		numeroElemento++;

		if(numeroElemento == 3){
            numeroElementoY++;
            numeroElemento = 0;
		}

        /* desenha o objeto */
        App.draw(this->objeto);
    }
}

/***** Método responsável por chamar todas as funções que desenham no programa *****/
void LexicographicPermute::desenharJogo(sf::RenderWindow &App){
    App.draw(this->painel);
    App.draw(this->background);
    this->desenharOpcoesControle(App);
    this->desenharFilaControle(App);
    this->desenharPermutacoes(App);
}

/****** OUTROS ********/
template <typename T>
std::string to_string(T value) {
    std::ostringstream os ;

    os << value ;

    return os.str() ;
}
