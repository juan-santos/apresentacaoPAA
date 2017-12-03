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

    background.setTexture(fundoJogo);
    //********** fim movimento fundo **********

    /* Load Menu font text */
    if (!this->font.loadFromFile("bin/Release/files/fonts/menu/bradley-hand-itc.ttf")) {
        std::cerr << "Error loading menu font text" << std::endl;
    }

    //textos do menu
    this->play.setFont(this->font);
    this->play.setString("Johnson Trotter");
    this->instrucoes.setFont(this->font);
    this->instrucoes.setString("Lexicographic Permute");
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
                                return JOHNSONTROTTER;
							case 1:
							    //tela de instruções
								return LEXICOGRAPHICPERMUTE;
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

                this->play.setColor(sf::Color(255, 0, 0, 255));
                this->play.setCharacterSize(70);
                this->play.setPosition({180.f, 250.f});

                this->instrucoes.setColor(sf::Color(0, 0, 0, 255));
                this->instrucoes.setCharacterSize(50);
                this->instrucoes.setPosition({150.f, 350});

                this->quit.setColor(sf::Color(0, 0, 0, 255));
                this->quit.setCharacterSize(50);
                this->quit.setPosition({370.f, 450});

			break;

			case 1:
                this->play.setColor(sf::Color(0, 0, 0, 255));
                this->play.setCharacterSize(50);
                this->play.setPosition({250, 250});

                this->instrucoes.setColor(sf::Color(255, 0, 0, 255));
                this->instrucoes.setCharacterSize(60);
                this->instrucoes.setPosition({120, 310});

                this->quit.setColor(sf::Color(0, 0, 0, 255));
                this->quit.setCharacterSize(50);
                this->quit.setPosition({370, 410});
			break;
			case 2:
                this->play.setColor(sf::Color(0, 0, 0, 255));
                this->play.setCharacterSize(50);
                this->play.setPosition({250, 250});

				this->instrucoes.setColor(sf::Color(0, 0, 0, 255));
				this->instrucoes.setCharacterSize(50);
				this->instrucoes.setPosition({150, 350});

				this->quit.setColor(sf::Color(255, 0, 0, 255));
				this->quit.setCharacterSize(70);
				this->quit.setPosition({360, 410});
			break;
			default:
			break;
		}

		/* Clear screen */
		App.clear();

		/* Draw screen */
		App.draw(this->background);
        App.draw(this->play);
		App.draw(this->instrucoes);
		App.draw(this->quit);

		/* Display menu */
		App.display();
	}

	return SAIR;
}
