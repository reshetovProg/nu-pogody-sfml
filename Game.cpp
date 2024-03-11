#include "Game.h"

Game::Game():
	window(sf::VideoMode(1200, 693), "Nu pogody")
{
	bgShape.setSize(sf::Vector2f(1200, 693));
	bgImage.loadFromFile("img/bg.png");
	bgShape.setTexture(&bgImage);
	screenShape.setSize(sf::Vector2f(637, 410));
	screenImage.loadFromFile("img/LU.png");
	screenShape.setTexture(&screenImage);
	screenShape.setPosition(sf::Vector2f(280, 138));
	sf::Vector2f pos1(94, 442);
	sf::Vector2f pos2(94, 565);
	sf::Vector2f pos3(1044, 442);
	sf::Vector2f pos4(1044, 565);
	buttons.push_back(Button(pos1));
	buttons.push_back(Button(pos2));
	buttons.push_back(Button(pos3));
	buttons.push_back(Button(pos4));

}

void Game::run()
{
	while (window.isOpen()) {
		processEvent();
		update();
		render();
	}
}

void Game::processEvent()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if ((event.type == sf::Event::MouseButtonPressed ||
			event.type == sf::Event::MouseButtonReleased)
			&& event.mouseButton.button==sf::Mouse::Left) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			int count = 0;
			for (auto& el : buttons) {
				if (el.getShape().getGlobalBounds().
					contains(float(mousePos.x), float(mousePos.y))) {
					el.changeStatus();
					wolfPosition = count;
					std::cout << wolfPosition;
				
				}
				count++;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			buttons[0].changeStatus();
			wolfPosition = 0;
			buttons[0].changeStatus();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			buttons[1].changeStatus();
			wolfPosition = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			buttons[2].changeStatus();
			wolfPosition = 2;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			buttons[3].changeStatus();
				wolfPosition = 3;
		}
		

	}

}

void Game::render()
{
	window.clear();
	window.draw(bgShape);
	window.draw(screenShape);
	for (auto el : buttons) {
		window.draw(el.getShape());
	}
	window.display();
}

void Game::update()
{
	switch (wolfPosition) {
	case 0:
		screenImage.loadFromFile("img/LU.png");
		screenShape.setTexture(&screenImage);
		break;
	case 1:
		screenImage.loadFromFile("img/LD.png");
		screenShape.setTexture(&screenImage);
		break;
	case 2:
		screenImage.loadFromFile("img/RU.png");
		screenShape.setTexture(&screenImage);
		break;
	case 3:
		screenImage.loadFromFile("img/RD.png");
		screenShape.setTexture(&screenImage);
		break;
	}
}
