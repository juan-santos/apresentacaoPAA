#include "Vitoria.h"

Vitoria::Vitoria() {
}

int Vitoria::Run(sf::RenderWindow &App) {

	sf::Event Event;
	sf::Texture Texture;
	sf::Sprite Sprite;
	sf::Font Font;
	sf::Text Menu1;
	sf::Text Menu2;

	bool Running = true;

	if (!Texture.loadFromFile("bin/Release/files/images/menu/vitoria.jpg")){
		std::cerr << "Error loading menu.png" << std::endl;
		//return (-1);
	}

	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(255, 255, 255, 255));

	if (!Font.loadFromFile("bin/Release/files/fonts/menu/crackman_front.ttf")){
		std::cerr << "Error loading font" << std::endl;
	}

  //escolho tamanho e fontes dos textos do menu
	Menu1.setFont(Font);
	Menu1.setCharacterSize(60);
	Menu1.setString("Sair");
	Menu1.setPosition({320.f,350.f });
	Menu1.setColor(sf::Color(255, 255, 255, 255));

	while (Running) {

		//Verifying events
		while (App.pollEvent(Event)) {

			// Window closed
			if (Event.type == sf::Event::Closed) {
				return (-1);
			}

			//Key pressed
			if (Event.type == sf::Event::KeyPressed) {

				switch (Event.key.code) {

                    case sf::Keyboard::Return:
                        return SAIR;

                    default:
                        break;
				}
			}
		}

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(Sprite);
        App.draw(Menu1);
		App.display();
	}

	return SAIR;
}
