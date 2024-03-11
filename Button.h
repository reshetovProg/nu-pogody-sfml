#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Button
{
	sf::CircleShape shape;
	bool status = false;
public:
	Button(sf::Vector2f);
	void changeStatus();
	bool getStatus();
	sf::Vector2f getPosition();
	sf::CircleShape& getShape();
};

