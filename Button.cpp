#include "Button.h"

Button::Button(sf::Vector2f position)
{
    shape.setRadius(29);
    shape.setFillColor(sf::Color(0,0,0,0));
    shape.setPosition(position);
}

void Button::changeStatus()
{
    status = !status;
    if (status) shape.setFillColor(sf::Color(0, 0, 0, 100));
    else shape.setFillColor(sf::Color(0, 0, 0, 0));
}

bool Button::getStatus()
{
    return status;
}

sf::Vector2f Button::getPosition()
{
    return shape.getPosition();
}

sf::CircleShape& Button::getShape()
{
    return shape;
}
