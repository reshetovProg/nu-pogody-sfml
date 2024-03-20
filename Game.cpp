#include "Game.h"

Game::Game():
	window(sf::VideoMode(1200, 693), "Nu pogody"),
	th(incrementer)
{
	liveTexture.loadFromFile("img/mistake.png");
	for (int i = 0; i < 3; i++) {
		sf::RectangleShape shape;
		shape.setTexture(&liveTexture);
		shape.setPosition(sf::Vector2f(310 + i * 40, 160));
		shape.setSize(sf::Vector2f(605, 340));
		lives.push_back(shape);
	}

	chickenShape.setSize(sf::Vector2f(605, 440));
	

	font.loadFromFile("Segment7.otf");
	countEggsText.setFont(font);
	countEggsText.setPosition(sf::Vector2f(650, 150));
	countEggsText.setFillColor(sf::Color::Black);
	countEggsText.setCharacterSize(60);

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

	eggImage.loadFromFile("img/egg.png");
	int posEgs[24][3] =	{	{330,265,20},
							{370,275,80},
							{400,300,140},
							{420,325,180},
							{440,350,220},
							{450,510,200}, //упало
							{330,365,20},
							{370,375,80},
							{400,400,140},
							{420,425,180},
							{440,450,220},
							{450,510,200}, //упало
							{870,293,200},
							{854,290,140},
							{820,288,80},
							{780,302,20},
							{745,345,-40},
							{765,510,200}, //упало
							{870,393,200},
							{854,390,140},
							{820,388,80},
							{780,402,20},
							{745,445,-40},
							{765,510,200}, //упало
	};
	for (int i = 0; i < 24; i++) {
			sf::RectangleShape shape;
			shape.setSize(sf::Vector2f(26, 19));
			shape.setTexture(&eggImage);
			shape.rotate(posEgs[i][2]);
			shape.setPosition(sf::Vector2f(posEgs[i][0], posEgs[i][1]));
			eggShapes.push_back(shape);		
	}

}

Game::~Game()
{
	th.join();
}

void Game::resetGame() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			eggStatus[i][j] = false;
		}
	}

	lvl = 1;
	speed = 10;
	spawnSpeed = 5;
	counterForSpawn = 0;

	
}

void Game::createRandomEgg()
{
	eggStatus[rand() % 4][0]=true;
}

void Game::showInfoByEggs()
{

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			std::cout << eggStatus[i][j] << " ";
		}
		std::cout << " : ";
	}
	std::cout << std::endl;
}

void Game::chickenAnimation()
{
	if (failSide < 2) {
		chickenShape.setPosition(sf::Vector2f(270, 138));
		std::string path = "img/chickenl" + std::to_string(statusChickenAnimation) + ".png";
		chickenTexture.loadFromFile(path);
		chickenShape.setTexture(&chickenTexture);
	}
	else {
		chickenShape.setPosition(sf::Vector2f(380, 138));
		std::string path = "img/chickenr" + std::to_string(statusChickenAnimation) + ".png";
		chickenTexture.loadFromFile(path);
		chickenShape.setTexture(&chickenTexture);
	}
}

void Game::moveEggs()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 5; j > 0; j--) {
			std::swap(eggStatus[i][j], eggStatus[i][j - 1]);
					
			if (j == 5 && eggStatus[i][j]==1) {
				//std::cout << i << " : " << wolfPosition << std::endl;
				if (i == wolfPosition) {
					eggStatus[i][j] = 0;
					countCatchedEggs++;
				}
			}
			if(j==5) {
				if (eggStatus[i][j] == 1) {
					mistake++;
					failSide = i;
					statusChickenAnimation = 1;
					resetGame();
				}
			}
			
		}
	}
}

void Game::run()
{
	while (window.isOpen()) {
		processEvent();
		update();
		render();
	}
}

void Game::gameOver() {
	resetGame();
	mistake = 0;
	countCatchedEggs = 0;
	value = 0;
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
					//std::cout << wolfPosition;
				
				}
				count++;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			buttons[0].changeStatus();
			wolfPosition = 0;
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

	
	for (int i = 0, count=0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (eggStatus[i][j]) {
				window.draw(eggShapes[count]);
			}
			count++;
		}
	}
	window.draw(countEggsText);
	for (int i = 0; i < mistake; i++) {
		window.draw(lives[i]);
	}
	if (statusChickenAnimation != 0) {
		while (statusChickenAnimation < 5) {
			chickenAnimation();
			statusChickenAnimation++;			
			window.clear();
			window.draw(bgShape);
			window.draw(screenShape);
			window.draw(chickenShape);
			window.draw(countEggsText);
			for (int i = 0; i < mistake; i++) {
				window.draw(lives[i]);
			}
			window.display();
			Sleep(600);
		}
		statusChickenAnimation = 0;
	}
	if (mistake == 3) {
		gameOver();
	}

	else window.display();
	
	
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

	if (value >= speed) {

		counterForSpawn++;
		moveEggs();
		//createRandomEgg();
		if (counterForSpawn >= spawnSpeed) {
			counterForSpawn = 0;
			createRandomEgg();
		}
		value = 0;
		//showInfoByEggs();
		if ((countCatchedEggs % (5*lvl)) == 0 && countCatchedEggs>0) {
			std::cout << countCatchedEggs << " : " << spawnSpeed << std::endl;
			if (spawnSpeed > 1) {
				spawnSpeed--;
				lvl++;
			}
		}

		if ((countCatchedEggs % (10 * lvl)) == 0 && countCatchedEggs > 0) {
			if (speed>4) speed--;
		}
			
	}

	countEggsText.setString(std::to_string(countCatchedEggs));

	




}

void Game::incrementer()
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		value++;
		//std::cout << value;
	
	}
	
}


int Game::value = 0;
