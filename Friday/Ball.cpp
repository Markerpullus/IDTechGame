#include "Ball.h"

Ball::Ball(float startX, float startY)
{
	score = 0;
	lives = 5;
	position.x = startX;
	position.y = startY;

	ballShape.setSize(sf::Vector2f(15, 15));
	ballShape.setPosition(position);
}


FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
}

RectangleShape Ball::getShape()
{
	return ballShape;
}

void Ball::incrementScore()
{
	score += 10;
}

void Ball::decrementLifeCount()
{
	lives--;
}

void Ball::resetLifeCount()
{
	lives = 5;
}

void Ball::resetScore()
{
	score = 0;
}

float Ball::getXVelocity()
{
	return xVelocity;
}

void Ball::reboundSides()
{
	xVelocity = -xVelocity;
}

void Ball::reboundBatOrTop()
{
	//position.y -= (yVelocity * 30);
	yVelocity = -yVelocity;
}

void Ball::hitBottom()
{
	position.y = 1;
	position.x = 500;
}

void Ball::update()
{
	position.y += yVelocity;
	position.x += xVelocity;

	ballShape.setPosition(position);
}