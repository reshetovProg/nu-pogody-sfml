#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>
#include <thread>
#include <chrono>

class Game
{
	sf::RenderWindow window;
	sf::RectangleShape bgShape;
	sf::Texture bgImage;
	sf::RectangleShape screenShape;
	sf::Texture screenImage;
	std::vector<Button> buttons;
	std::vector<sf::RectangleShape> eggShapes;
	sf::Texture eggImage;
	sf::Text countEggsText;
	sf::Font font;
	int wolfPosition = 3; //0-LU 1-LD 2-RU 3-RD
	bool eggStatus[4][6]{};
	
	const sf::Time TimePerFrame = sf::seconds(1.f / 10.f);
	std::thread th;
	int static value;
	int lvl = 1;
	int speed = 10;
	int spawnSpeed = 5;
	int counterForSpawn=0;
	int countCatchedEggs = 0;
	int mistake = 0;


public:
	Game();
	~Game();
	void run();
private:
	void static incrementer();
	void processEvent();
	void render();
	void update();
	void createRandomEgg();
	void moveEggs();
	void showInfoByEggs();
	void resetGame();
};

