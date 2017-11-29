#include "Instrucao.h"

Instrucao::Instrucao() {
}

int Instrucao::Run(sf::RenderWindow &App) {

	sf::Event Event;
	sf::Texture Texture;
	sf::Sprite Sprite;

	bool Running = true;

	if (!Texture.loadFromFile("bin/Release/files/images/menu/instrucao.jpg")){
		std::cerr << "Error loading menu.png" << std::endl;
	}

	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(255, 255, 255, 255));

	while (Running) {

		//Verifying events
		while (App.pollEvent(Event)) {

			// Window closed
			if (Event.type == sf::Event::Closed) {
				return SAIR;
			}

			//Key pressed
			if (Event.type == sf::Event::KeyPressed) {

				switch (Event.key.code) {

                    case sf::Keyboard::Return:
                        return MENU;

                    default:
                        break;
				}
			}
		}

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(Sprite);
        App.display();
	}

	return SAIR;
}
