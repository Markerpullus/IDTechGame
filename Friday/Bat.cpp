#include "Bat.h"

Bat::Bat(float startX, float startY)
{
	position.x = startX;
	position.y = startY;
	batShape.setSize(sf::Vector2f(100, 10));
	batShape.setPosition(position);
}

FloatRect Bat::getPosition()
{
	return batShape.getGlobalBounds();
}

RectangleShape Bat::getShape()
{
	return batShape;
}

void Bat::decrementSize()
{
	Vector2f oldSize = batShape.getSize();
	batShape.setSize(Vector2f(oldSize.x - 10, oldSize.y));
}

void Bat::moveLeft()
{
	position.x -= batSpeed;
}

void Bat::moveRight()
{
	position.x += batSpeed;
}

void Bat::update()
{
	batShape.setPosition(position);
}