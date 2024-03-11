#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>
class Game
{
	sf::RenderWindow window;
	sf::RectangleShape bgShape;
	sf::Texture bgImage;
	sf::RectangleShape screenShape;
	sf::Texture screenImage;
	std::vector<Button> buttons;
	int wolfPosition = 0; //0-LU 1-LD 2-RU 3-RD

public:
	Game();
	void run();
private:
	void processEvent();
	void render();
	void update();
};

