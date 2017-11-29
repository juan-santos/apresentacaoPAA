#include "Menu.h"

Menu::Menu() {
	this->playing = false;

    /* Load Menu sound */
    if (!this->sound.openFromFile("bin/Release/files/sounds/menu/the_field_of_dreams.ogg")) {
      std::cerr << "Error loading menu sound" << std::endl;
    }

	//se achar a imagem de fundo
    if (!this->fundoJogo.loadFromFile("bin/Release/files/images/menu/background.png")){
        std::cerr << "Error loading menu image" << std::endl;
    }

    //********** início movimento no fundo **********

    this->fundoJogoMovimento.setSpriteSheet(this->fundoJogo);
    this->fundoJogoMovimento.addFrame(sf::IntRect(0, 0, 800, 600));
    this->fundoJogoMovimento.addFrame(sf::IntRect(800, 0, 800, 600));
    this->fundoJogoMovimento.addFrame(sf::IntRect(0, 600, 800, 600));
    this->fundoJogoMovimento.addFrame(sf::IntRect(800, 600, 800, 600));

    this->background.setPosition(0,0);
    //********** fim movimento fundo **********

    /* Load Menu font text */
    if (!this->font.loadFromFile("bin/Release/files/fonts/menu/crackman_front.ttf")) {
        std::cerr << "Error loading menu font text" << std::endl;
    }

    //textos do menu
    this->play.setFont(this->font);
    this->play.setString("Start");
    this->back.setFont(this->font);
    this->back.setString("Continue");
    this->instrucoes.setFont(this->font);
    this->instrucoes.setString("Instructions");
    this->quit.setFont(this->font);
    this->quit.setString("Exit");
}

int Menu::Run(sf::RenderWindow &App) {

    //evento do teclado
    sf::Event event;

    //opção atual do menu
    int opt = 0;

    this->sound.setLoop(true); /* sound loop */
    this->sound.play(); /* play music */

	while (true) {

        //****** início do movimento *******
        sf::Time frameTime = this->frameClock.restart();
        this->background.play(this->fundoJogoMovimento);

        // muda a imagem
        this->background.update(frameTime);
        //****** fim do movimento ******

		/* Parse Events */
		while (App.pollEvent(event)) {

			/* Windows closed */
			if (event.type == sf::Event::Closed)
				return -1;

			//Key pressed
			if (event.type == sf::Event::KeyPressed) {

				switch (event.key.code) {

				    //se for a tecla pra cima
					case sf::Keyboard::Up:

                            opt = (opt > 0)? --opt : opt = 2;

                        break;

                    //se for a tecla pra baixo
					case sf::Keyboard::Down:

                        opt = (opt < 2)? ++opt : opt = 0;

                        break;

                    //se for a tecla esc
					case sf::Keyboard::Escape:
						return -1;
                        break;

                    //se for a tecla enter
					case sf::Keyboard::Return:
						switch(opt) {
							case 0:
							    //jogo
                                this->playing = true;
                                return GAME;
							case 1:
							    //tela de instruções
								return INSTRUCAO;
							case 2:
							    //sair
								return SAIR;
							default:
							    //não existe este caso
								return SAIR;
						}
                        break;

					default:
                        break;
				}
			}
		}

		switch(opt) {
			case 0:

                this->play.setColor(sf::Color(253, 206, 220, 255));
                this->play.setCharacterSize(110);
                this->play.setPosition({240.f, 150.f});

                this->back.setColor(sf::Color(253, 206, 220, 255));
                this->back.setCharacterSize(110);
                this->back.setPosition(100,150);

                this->instrucoes.setColor(sf::Color(162, 132, 140, 255));
                this->instrucoes.setCharacterSize(60);
                this->instrucoes.setPosition({170.f, 300.f});

                this->quit.setColor(sf::Color(162, 132, 140, 255));
                this->quit.setCharacterSize(60);
                this->quit.setPosition({335.f, 400.f});

			break;

			case 1:
                this->play.setColor(sf::Color(162, 132, 140, 255));
                this->play.setCharacterSize(60);
                this->play.setPosition({315.f, 200.f});

                this->back.setColor(sf::Color(162, 132, 140, 255));
                this->back.setCharacterSize(60);
                this->back.setPosition({240.f, 200.f});

                this->instrucoes.setColor(sf::Color(253, 206, 220, 255));
                this->instrucoes.setCharacterSize(85);
                this->instrucoes.setPosition({90.f, 280.f});

                this->quit.setColor(sf::Color(162, 132, 140, 255));
                this->quit.setCharacterSize(60);
                this->quit.setPosition({335.f, 400.f});
			break;
			case 2:
				this->play.setColor(sf::Color(162, 132, 140, 255));
				this->play.setCharacterSize(60);
				this->play.setPosition({315.f, 200.f});

				this->back.setColor(sf::Color(162, 132, 140, 255));
				this->back.setCharacterSize(60);
				this->back.setPosition({240.f, 200.f});

				this->instrucoes.setColor(sf::Color(162, 132, 140, 255));
				this->instrucoes.setCharacterSize(60);
				this->instrucoes.setPosition({170.f, 300.f});

				this->quit.setColor(sf::Color(253, 206, 220, 255));
				this->quit.setCharacterSize(85);
				this->quit.setPosition({285.f, 380.f});
			break;
			default:
			break;
		}

		/* Clear screen */
		App.clear();

		/* Draw screen */
		App.draw(this->background);

		/* Display menu options */
		if (this->playing) {
			App.draw(this->back);
		} else {
			App.draw(this->play);
		}

		App.draw(this->instrucoes);
		App.draw(this->quit);

		/* Display menu */
		App.display();
	}

	return SAIR;
}
