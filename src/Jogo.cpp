#include "Jogo.h"

Jogo::Jogo() {

    this->fase = 1;

    if (!this->sound.openFromFile("bin/Release/files/sounds/menu/pegar.ogg")) {
              std::cerr << "Error loading menu sound" << std::endl;
    }

    /*********** PAINEL *******************/
    if(!this->backgroundPainel.loadFromFile("bin/Release/files/images/jogo/painel.jpg")){
         std::cerr << "Error loading painel" << std::endl;
    }

    this->painel.setPosition(600, 0);
    this->painel.setTexture(this->backgroundPainel);

    /*********** ITENS MAPA *******************/
    //itens do mapa
    if (!this->itens[CONCRETO].loadFromFile("bin/Release/files/images/jogo/concreto.png")
        || !this->itens[GRAMA].loadFromFile("bin/Release/files/images/jogo/grama.png")
        || !this->itens[PEDRA].loadFromFile("bin/Release/files/images/jogo/pedra.jpg")
        || !this->itens[AGUA].loadFromFile("bin/Release/files/images/jogo/agua.png")
        || !this->itens[PAREDE].loadFromFile("bin/Release/files/images/jogo/parede.png")
        || !this->itens[OBJ1].loadFromFile("bin/Release/files/images/jogo/obj1.png")
        || !this->itens[OBJ2].loadFromFile("bin/Release/files/images/jogo/obj2.png")
        || !this->itens[OBJ3].loadFromFile("bin/Release/files/images/jogo/obj3.png")
        || !this->itens[OBJ4].loadFromFile("bin/Release/files/images/jogo/obj4.png")
        || !this->itens[OBJ5].loadFromFile("bin/Release/files/images/jogo/obj5.png")
        ){
         std::cerr << "Error loading itens" << std::endl;
    }


    /************* Personagem ***************/

    if (!texture.loadFromFile("bin/Release/files/images/jogo/player2.png")) {
         std::cerr << "Error loading personagem" << std::endl;
    }

    //todas as direções possiveis do personagem
    this->walkingAnimationDown.setSpriteSheet(texture);
    this->walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    this->walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    this->walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    this->walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    this->walkingAnimationLeft.setSpriteSheet(texture);
    this->walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    this->walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    this->walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    this->walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    this->walkingAnimationRight.setSpriteSheet(texture);
    this->walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    this->walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    this->walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    this->walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    this->walkingAnimationUp.setSpriteSheet(texture);
    this->walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    this->walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    this->walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    this->walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    this->animatedSprite = AnimatedSprite(sf::seconds(0.04), true, false);

    this->speed = 1.f;
    this->movimento = false;

    this->sentido = 2;
    this->currentAnimation = &walkingAnimationDown;
    this->animatedSprite.setPosition(POS_INICIAL_X,POS_INICIAL_Y);

    animatedSprite.play(*currentAnimation);
    animatedSprite.stop();


    /************* BOTOES ***************/

    if (!this->controle[SEGUIR].loadFromFile("bin/Release/files/images/jogo/seguir.png")
        ||!this->controle[HORARIO].loadFromFile("bin/Release/files/images/jogo/horario.png")
        ||!this->controle[ANTIHORARIO].loadFromFile("bin/Release/files/images/jogo/antihorario.png")
        ||!this->controle[FUNCAO1].loadFromFile("bin/Release/files/images/jogo/f2.png")
        ||!this->controle[FUNCAO2].loadFromFile("bin/Release/files/images/jogo/g2.png")
        ||!this->controle[PEGAR].loadFromFile("bin/Release/files/images/jogo/pegar.png")
        ||!this->controle[LIMPAR].loadFromFile("bin/Release/files/images/jogo/limpar.png")
        ||!this->controle[EXECUTAR].loadFromFile("bin/Release/files/images/jogo/executar.png")
        ){
        std::cout << "Can't find the ITEM" << std::endl;
    }

    this->seguir.setPosition(630, 30);
    this->seguir.setTexture(controle[SEGUIR]);

    this->horario.setPosition(675, 30);
    this->horario.setTexture(controle[HORARIO]);

    this->antihorario.setPosition(730, 30);
    this->antihorario.setTexture(controle[ANTIHORARIO]);

    this->funcao1.setPosition( 630, 80 );
    this->funcao1.setTexture(controle[FUNCAO1]);

    this->funcao2.setPosition( 675, 80 );
    this->funcao2.setTexture(controle[FUNCAO2]);

    this->pegar.setPosition( 730.0f, 80 );
    this->pegar.setTexture(controle[PEGAR]);

    this->limpar.setPosition( 650, 550 );
    this->limpar.setTexture(controle[LIMPAR]);

    this->executar.setPosition( 720, 550 );
    this->executar.setTexture(controle[EXECUTAR]);

}

int Jogo::Run(sf::RenderWindow &App) {
    //evento do teclado
    int executar = 0;
    sf::Event event;

    this->carregarMapaAtual(App, this->fase);

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
			if(executar != GAME){
                return executar;
			}
        }


        //Acabaram as fases
        if(this->fase > NUMERO_FASES){
            return VITORIA;
        }

        App.clear();
        this->desenharOpcoesControle(App);
        this->desenharJogo(App);
        App.display();
    }

    return SAIR;
}


/****** EXECUCAO *********/
 int Jogo::executarFilaControle(sf::RenderWindow &App){
     int fase = this->fase;
     bool sucesso = this->observarJogador(App, true);

     if(!sucesso){
        //se houver algum erro nos comandos
        return ERRO;
     }else{

         //se avançar de fase, mudo o mapa
         if(fase != this->fase){

                //se houver mais fases
                if(this->fase <= NUMERO_FASES){
                    //carrego a próxima
                    this->carregarMapaAtual(App, this->fase);
                }else{
                    //vou para a tela de vitória
                    return VITORIA;
                }
         }
     }

     //continuo no jogo
     return GAME;
 }


/***** BOTOES *****/

int Jogo::funcionalidadeBotao(sf::RenderWindow &App, sf::Event &event){
    int operacao = GAME;
    if(!this->movimento)
        switch (event.type) {

            //se o mouse mover
            case sf::Event::MouseMoved: {

                sf::Vector2i mousePos = sf::Mouse::getPosition( App );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                if (this->seguir.getGlobalBounds().contains( mousePosF ) ) {
                    this->seguir.setColor( sf::Color( 250, 20, 20 ) );
                } else {
                    this->seguir.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->horario.getGlobalBounds().contains( mousePosF ) ) {
                    this->horario.setColor( sf::Color( 250, 20, 20 ) );
                } else {
                    this->horario.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->antihorario.getGlobalBounds().contains( mousePosF ) ) {
                    this->antihorario.setColor( sf::Color( 250, 20, 20 ) );
                } else {
                    this->antihorario.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->funcao1.getGlobalBounds().contains( mousePosF ) ) {
                    this->funcao1.setColor( sf::Color( 250, 20, 20 ) );
                } else {
                    this->funcao1.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->funcao2.getGlobalBounds().contains( mousePosF ) ) {
                    this->funcao2.setColor( sf::Color( 250, 20, 20 ) );
                } else {
                    this->funcao2.setColor( sf::Color( 255, 255, 255 ) );
                }

                if (this->pegar.getGlobalBounds().contains( mousePosF ) ) {
                    this->pegar.setColor( sf::Color( 250, 20, 20 ) );
                } else {
                    this->pegar.setColor( sf::Color( 255, 255, 255 ) );
                }
                break;
            }

            case sf::Event::MouseButtonPressed: {

                sf::Vector2i mousePos = sf::Mouse::getPosition( App );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                if (this->seguir.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {

                            //número máximo de comandos
                        if(this->pilha.getTamanho() < 30)
                            this->pilha.Insere(SEGUIR);
                    } else {
                        if (event.mouseButton.button == sf::Mouse::Middle) {

                            //número máximo de comandos
                            if(this->pilhafuncao1.getTamanho() < 10)
                                this->pilhafuncao1.Insere(SEGUIR);
                        } else{
                            if (event.mouseButton.button == sf::Mouse::Right) {

                                //número máximo de comandos
                                if(this->pilhafuncao2.getTamanho() < 10)
                                    this->pilhafuncao2.Insere(SEGUIR);
                            }
                        }
                    }
                }

                if (this->horario.getGlobalBounds().contains( mousePosF ) ) {
                    std::cout << "horario" << std::endl;

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        //número máximo de comandos
                        if(this->pilha.getTamanho() < 30)
                            this->pilha.Insere(HORARIO);
                    } else {

                        if (event.mouseButton.button == sf::Mouse::Middle) {
                            //número máximo de comandos
                            if(this->pilhafuncao1.getTamanho() < 10)
                                this->pilhafuncao1.Insere(HORARIO);
                        } else{

                            if (event.mouseButton.button == sf::Mouse::Right) {

                                //número máximo de comandos
                            if(this->pilhafuncao2.getTamanho() < 10)
                                this->pilhafuncao2.Insere(HORARIO);
                            }
                        }
                    }
                }

                if (this->antihorario.getGlobalBounds().contains( mousePosF ) ) {
                    std::cout << "antihorario" << std::endl;

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        //número máximo de comandos
                        if(this->pilha.getTamanho() < 30)
                            this->pilha.Insere(ANTIHORARIO);
                    } else {

                        if (event.mouseButton.button == sf::Mouse::Middle) {
                            if(this->pilhafuncao1.getTamanho() < 10)
                                this->pilhafuncao1.Insere(ANTIHORARIO);
                        } else{

                            if (event.mouseButton.button == sf::Mouse::Right) {
                                if(this->pilha.getTamanho() < 10)
                                    this->pilhafuncao1.Insere(ANTIHORARIO);
                            }
                        }
                    }
                }

                if (this->funcao1.getGlobalBounds().contains( mousePosF ) ) {
                    std::cout << "funcao 1" << std::endl;

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        //número máximo de comandos
                        if(this->pilha.getTamanho() < 30)
                            this->pilha.Insere(FUNCAO1);
                    }
                }

                if (this->funcao2.getGlobalBounds().contains( mousePosF ) ) {
                    std::cout << "funcao 2" << std::endl;

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        //número máximo de comandos
                        if(this->pilha.getTamanho() < 30)
                            this->pilha.Insere(FUNCAO2);
                    }
                }

                if (this->pegar.getGlobalBounds().contains( mousePosF ) ) {
                    std::cout << "pegar 2" << std::endl;

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        //número máximo de comandos
                        if(this->pilha.getTamanho() < 30)
                            this->pilha.Insere(PEGAR);

                    } else {

                        if (event.mouseButton.button == sf::Mouse::Middle) {

                                //número máximo de comandos
                            if(this->pilhafuncao1.getTamanho() < 10)
                                this->pilhafuncao1.Insere(PEGAR);
                            } else{

                                if (event.mouseButton.button == sf::Mouse::Right) {
                                    if(this->pilhafuncao2.getTamanho() < 10)
                                        this->pilhafuncao2.Insere(PEGAR);
                                }
                        }
                    }
                }

                if (this->limpar.getGlobalBounds().contains( mousePosF ) ) {
                    std::cout << "limpar" << std::endl;

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int ultimo;
                        this->pilha.Retira(ultimo);
                    } else {
                        if (event.mouseButton.button == sf::Mouse::Middle) {
                            int ultimo;
                            this->pilhafuncao1.Retira(ultimo);
                        } else{
                            if (event.mouseButton.button == sf::Mouse::Right) {
                                int ultimo;
                                this->pilhafuncao2.Retira(ultimo);
                            }
                        }
                    }
                }

                if (this->executar.getGlobalBounds().contains( mousePosF ) ) {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                         std::cout << "EXECUTAR" << std::endl;
                         //retorno o resultado obtido do comando
                         operacao = this->executarFilaControle(App);
                    }
                }

                break;
            }
        }

        return operacao;
}

void Jogo::desenharOpcoesControle(sf::RenderWindow &App){

    if(!this->movimento){
        //desenho os botões
        App.draw(seguir);
        App.draw(horario);
        App.draw(antihorario);
        App.draw(funcao1);
        App.draw(funcao2);
        App.draw(pegar);

        App.draw(limpar);
        App.draw(executar);
    }


}

void Jogo::desenharFilaControle(sf::RenderWindow &App){
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
		objeto.setPosition(625 + numeroElemento * 30 , 150 + numeroElementoY * 32);

		numeroElemento++;

		if(numeroElemento == 5){
            numeroElementoY++;
            numeroElemento = 0;
		}

        /* desenha o objeto */
        App.draw(this->objeto);
    }
}

void Jogo::desenharFilaControleF1(sf::RenderWindow &App){
    /* pilha auxiliar para desenhar os objetos */
	Pilha<int> paux;
	int aux;

	while (!this->pilhafuncao1.EstaVazia()) {
		this->pilhafuncao1.Retira(aux);
		paux.Insere(aux);
	}

	int numeroElemento = 0;
	int numeroElementoY = 0;
	/* agora que paux possui pilha invertida, reinserimos os valores em pilha na ordem correta e aproveitamos para desenhar o objeto! */
	while (!paux.EstaVazia()) {
		paux.Retira(aux);

		/* inserimos o elemento de volta na stack */
		pilhafuncao1.Insere(aux);

		objeto.setTexture(this->controle[aux]);
		objeto.setPosition(625 + numeroElemento * 30 , 380 + numeroElementoY * 30);

		numeroElemento++;

		if(numeroElemento == 5){
            numeroElementoY++;
            numeroElemento = 0;
		}

        /* desenha o objeto */
        App.draw(this->objeto);
    }
}

void Jogo::desenharFilaControleF2(sf::RenderWindow &App){
    /* pilha auxiliar para desenhar os objetos */
	Pilha<int> paux;
	int aux;

	while (!this->pilhafuncao2.EstaVazia()) {
		this->pilhafuncao2.Retira(aux);
		paux.Insere(aux);
	}

	int numeroElemento = 0;
	int numeroElementoY = 0;
	/* agora que paux possui pilha invertida, reinserimos os valores em pilha na ordem correta e aproveitamos para desenhar o objeto! */
	while (!paux.EstaVazia()) {
		paux.Retira(aux);

		/* inserimos o elemento de volta na stack */
		pilhafuncao2.Insere(aux);

		objeto.setTexture(this->controle[aux]);
		objeto.setPosition(625 + numeroElemento * 30 , 470 + numeroElementoY * 30);

		numeroElemento++;

		if(numeroElemento == 5){
            numeroElementoY++;
            numeroElemento = 0;
		}

        /* desenha o objeto */
        App.draw(this->objeto);
    }
}

/******** PERSONAGEM *********/

void Jogo::resetarJogador(sf::RenderWindow &App){
    this->animatedSprite.setPosition(POS_INICIAL_X,POS_INICIAL_Y);
    this->sentido = 2;
    this->currentAnimation = &walkingAnimationDown;

    animatedSprite.play(*currentAnimation);
    animatedSprite.stop();
    App.draw(animatedSprite);
    Sleep(200);
}

bool Jogo::observarJogador(sf::RenderWindow &App, bool executarMovimentos){
    bool sucesso = true;

    //se o personagem já não estiver se movimentando, através do método movimentarPersonagem
    if(!this->movimento){

         //se a função for chamada pra mostrar o jogador se movimentando
         if(executarMovimentos){
             //carrego a fase atual
            this->carregarMapaAtual(App, this->fase);
            this->resetarJogador(App);
            this->movimento = true;

            if(this->movimentarPersonagem(App, this->pilha)){

                //se o usuario tiver pegado todos os itens do mapa
                if(this->numeroItensMapa() == 0){
                    cout << this->numeroItensMapa()<< endl;
                    this->fase++;
                    this->resetarJogador(App);
                }
                else{
                    sucesso = false;
                }
            }
            else{
                sucesso = false;
            }

            this->movimento = false;

        } else{
            //se a funcao for chamada pra mostrar o jogador no mapa, apenas
            animatedSprite.play(*currentAnimation);

            animatedSprite.stop();
            App.draw(animatedSprite);
        }
    }

    return sucesso;
}

bool Jogo::movimentarPersonagem(sf::RenderWindow &App, Pilha<int> &pilha){

    Pilha<int> paux;

    int aux = -1;
    int aux2 = -1;
    int x, y;

	while (!pilha.EstaVazia()) {
        pilha.Retira(aux);
		paux.Insere(aux);
	}

	//variavel que verificará se o usuário fizer algum caminho errado
    bool ok = true;

    while (!paux.EstaVazia()) {
        paux.Retira(aux2);
        pilha.Insere(aux2);

        //se o caminho for traçado corretamente e não houver erro
        if(ok){
            noKeyWasPressed = false;
            sf::Vector2f movement(0.f, 0.f);

            switch(aux2){
                case SEGUIR:

                        cout << "Comando: seguir" <<endl;
                        noKeyWasPressed = true; //mudar o local da variavel

                        switch(this->sentido){

                            //pra cima
                            case 0:
                                x = this->descobrirX(this->animatedSprite.getPosition().x);
                                cout << "Posicao X: " << this->animatedSprite.getPosition().x << ", " << x << endl;

                                y = this->descobrirY(this->animatedSprite.getPosition().y - TAMANHO_ITEM);
                                cout << "Posicao Y: "<<this->animatedSprite.getPosition().y - TAMANHO_ITEM << ", " << y <<endl;

                                if(!podeSeguir(x,y)){
                                    cout << "NAO PODE PROSSEGUIR" << endl;
                                    ok = false;
                                    continue;
                                }
                                movement.y -= speed;
                                break;

                            //esquerda
                            case 1:
                                x = this->descobrirX(this->animatedSprite.getPosition().x - TAMANHO_ITEM);
                                cout << "Posicao X: " << this->animatedSprite.getPosition().x - TAMANHO_ITEM << ", " << x << endl;

                                y = this->descobrirY(this->animatedSprite.getPosition().y );
                                cout << "Posicao Y: "<<this->animatedSprite.getPosition().y << ", " << y <<endl;

                                if(!podeSeguir(x,y)){
                                    cout << "NAO PODE PROSSEGUIR" << endl;
                                    ok = false;
                                    continue;
                                }
                                movement.x -= speed;
                                break;

                            //pra baixo
                            case 2:
                                x = this->descobrirX(this->animatedSprite.getPosition().x);
                                cout << "Posicao X: " << this->animatedSprite.getPosition().x << ", " << x << endl;

                                y = this->descobrirY(this->animatedSprite.getPosition().y + TAMANHO_ITEM);
                                cout << "Posicao Y: "<<this->animatedSprite.getPosition().y + TAMANHO_ITEM << ", " << y <<endl;

                                if(!podeSeguir(x,y)){
                                    ok = false;
                                    cout << "NAO PODE PROSSEGUIR" << endl;
                                    continue;
                                }
                                movement.y += speed;
                                break;

                            //pra direita
                            case 3:

                                x = this->descobrirX(this->animatedSprite.getPosition().x + TAMANHO_ITEM);
                                cout << "Posicao X: " << this->animatedSprite.getPosition().x + TAMANHO_ITEM << ", " << x << endl;

                                y = this->descobrirY(this->animatedSprite.getPosition().y );
                                cout << "Posicao Y: "<<this->animatedSprite.getPosition().y << ", " << y <<endl;

                                if(!podeSeguir(x,y)){
                                    cout << "NAO PODE PROSSEGUIR" << endl;
                                    ok = false;
                                    continue;
                                }
                                movement.x += speed;
                                break;
                        }
                    break;

                case HORARIO:
                    cout << "Comando: horario" <<endl;

                    if(this->sentido > 0){
                        this->sentido--;
                    } else{
                        this->sentido = 3;
                    }

                    switch(this->sentido){
                        //pra cima
                        case 0:
                            currentAnimation = &walkingAnimationUp;
                            break;
                        //esquerda
                        case 1:
                            currentAnimation = &walkingAnimationLeft;
                            break;
                        //pra baixo
                        case 2:
                            currentAnimation = &walkingAnimationDown;
                            break;
                        //pra direita
                        case 3:
                            currentAnimation = &walkingAnimationRight;
                            break;
                    }
                    break;

                case ANTIHORARIO:

                    if(this->sentido < 3){
                        this->sentido++;
                    } else{
                        this->sentido = 0;
                    }

                    switch(sentido){
                        //pra cima
                        case 0:
                            currentAnimation = &walkingAnimationUp;
                            break;
                        //esquerda
                        case 1:
                            currentAnimation = &walkingAnimationLeft;
                            break;
                        //pra baixo
                        case 2:
                            currentAnimation = &walkingAnimationDown;
                            break;
                        //pra direita
                        case 3:
                            currentAnimation = &walkingAnimationRight;
                            break;
                    }
                    break;

                case FUNCAO1:
                    cout << "Comando: f1" <<endl;

                    if(!this->movimentarPersonagem(App, this->pilhafuncao1)){
                        ok = false;
                        continue;
                    }
                    break;

                case FUNCAO2:
                    cout << "Comando: f2" <<endl;

                    if(!this->movimentarPersonagem(App, this->pilhafuncao2)){
                        ok = false;
                        continue;
                    }
                    break;

                case PEGAR:
                    cout << "Comando: pegar" <<endl;
                    x = this->descobrirX(this->animatedSprite.getPosition().x);
                    cout << "Posicao X: " << this->animatedSprite.getPosition().x << ", " << x << endl;
                    y = this->descobrirY(this->animatedSprite.getPosition().y);
                    cout << "Posicao Y: "<<this->animatedSprite.getPosition().y << ", " << y <<endl;
                    this->pegarItem(x,y);
                    break;

            }

            // if no key was pressed stop the animation
            if (!noKeyWasPressed) {

                sf::Time frameTime = frameClock.restart();

                this->animatedSprite.play(*currentAnimation);
                this->animatedSprite.stop();
                this->animatedSprite.update(frameTime);

                // draw
                App.clear();
                this->desenharJogo(App);
                App.draw(this->animatedSprite);
                App.display();

                Sleep(1000);

            }else{

                for(int i = 0; i < 30;i++){
                    Sleep(70);
                    this->animatedSprite.play(*currentAnimation);

                    sf::Time frameTime = frameClock.restart();


                    this->animatedSprite.move(movement);
                    this->animatedSprite.update(sf::seconds(0.4f));

                    //o jogador fez algum movimento que causou a morte dele
                    if(this->morre(this->descobrirX(this->animatedSprite.getPosition().x),
                                               this->descobrirY(this->animatedSprite.getPosition().y))){
                        cout << "MORRE" << endl;
                        ok = false;
                    }

                    // draw
                    App.clear();
                    this->desenharJogo(App);
                    App.draw(this->animatedSprite);
                    App.display();
                }
            }

            noKeyWasPressed = false;
        }
    }

    return ok;
}

void Jogo::desenharJogo(sf::RenderWindow &App){
    App.draw(this->painel);
    this->desenharMapaAtual(App);
    this->desenharOpcoesControle(App);
    this->desenharFilaControle(App);
    this->desenharFilaControleF1(App);
    this->desenharFilaControleF2(App);
    this->observarJogador(App, false);
}

/************ VERIFICA ITENS ********/
int Jogo::descobrirX(const float x) const{
    return (x / TAMANHO_ITEM);
}

int Jogo::descobrirY(const float y) const{
    return (y / TAMANHO_ITEM);
}

bool Jogo::podeSeguir(const int x, const int y) const {

    return (estaNoIntervaloDoMapa(x,y)
            && this->mapaAtual[y][x] != PEDRA);
}

bool Jogo::morre(const int x, const int y) const{
    return this->mapaAtual[y][x] == AGUA;
}

bool Jogo::ehItemMapa(const int x, const int y) const {

    if(estaNoIntervaloDoMapa(x, y))
        return  ((this->mapaAtual[y][x] == OBJ1) ||(this->mapaAtual[y][x] == OBJ2)
                 ||(this->mapaAtual[y][x] == OBJ3) ||(this->mapaAtual[y][x] == OBJ4)
                 || (this->mapaAtual[y][x] == OBJ5));

    return false;
}

bool Jogo::estaNoIntervaloDoMapa(const int x, const int y) const {
    return ((x > -1 && x < NRO_CASAS) && ((y > -1 && y < NRO_CASAS)));
}

int Jogo::numeroItensMapa() const{
    int nroItens = 0;

    //percorro as colunas
    for(int i = 0; i <NRO_CASAS; i++){

        //percorro as linhas
        for(int j = 0; j <NRO_CASAS; j++){

            //SE FOR ITEM
            if(this->ehItemMapa(j,i))
                nroItens++;
        }
    }
    return nroItens;
}

bool Jogo::pegarItem(const int x, const int y){

    if(estaNoIntervaloDoMapa(x,y)){

        if(this->ehItemMapa(x,y)){
            this->sound.play();
            this->mapaAtual[y][x] = PAREDE;
            return true;
        }
    }

    return false;
}

/************ MAPA ******************/

void Jogo::desenharMapaAtual(sf::RenderWindow &App){

    //percorro as colunas
    for(int i = 0; i <NRO_CASAS; i++){

        //percorro as linhas
        for(int j = 0; j <NRO_CASAS; j++){
            //percorro cada posicao da matriz

            mapa.setTexture(this->itens[this->mapaAtual[i][j]]);
            mapa.setPosition(j*TAMANHO_ITEM, i*TAMANHO_ITEM);
            //desenha o item no mapa
            App.draw(mapa);
        }
    }
}

void Jogo::carregarMapaAtual(sf::RenderWindow &App, int fase){
    string linha, nomeArquivo;
    ifstream arquivo;
    int x , y, tamanhoString;

    //limpo a matriz
    for(int y = 0;y <NRO_CASAS; y++){

        for(int x = 0; x <NRO_CASAS; x++){
            this->mapaAtual[y][x] = -1;
        }

        cout <<endl;
    }

    //escolho o arquivo da fase atual
    switch(fase){
        case 1:
            arquivo.open("bin/Release/files/fases/mapa1.txt");
        break;
        case 2:
            arquivo.open("bin/Release/files/fases/mapa2.txt");
            break;
        case 3:
            arquivo.open("bin/Release/files/fases/mapa3.txt");
            break;
        case 4:
            arquivo.open("bin/Release/files/fases/mapa4.txt");
            break;
        case 5:
            arquivo.open("bin/Release/files/fases/mapa5.txt");
            break;
        default:
            //arquivo default
            arquivo.open("bin/Release/files/fases/mapa0.txt");
            break;
    }

    //se o arquivo estiver aberto
    if(arquivo.is_open()){

        y = 0;
        //enquanto houver linha no arquivo e não for maior que o tamanho máximo
        while((getline(arquivo, linha)) && (y < NRO_CASAS)){

            //tamanho da linha atual
            tamanhoString = linha.length();

            for(x = 0; (x < NRO_CASAS) && (x < tamanhoString); x++){

                //obtenho o char do valor e transformo no int
                this->mapaAtual[y][x] = linha[x]-48;
            }

            //incremento as linhas
            y++;
        }
    }
}


/****** OUTROS ********/

template <typename T>
std::string to_string(T value) {
    std::ostringstream os ;

    os << value ;

    return os.str() ;
}
