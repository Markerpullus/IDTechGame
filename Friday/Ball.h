#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Ball
{
private:
	Vector2f position;
	RectangleShape ballShape;

	int score;
	int lives;

	float xVelocity = 7.0f;
	float yVelocity = 7.0f;

public:
	Ball(float startX, float startY);
	FloatRect getPosition();
	RectangleShape getShape();
	
	inline int getLifeCount() { return lives; }
	void decrementLifeCount();
	void resetLifeCount();
	void incrementScore();
	void resetScore();
	inline int getScore() { return score; }

	float getXVelocity();
	void reboundSides();
	void reboundBatOrTop();
	void hitBottom();
	void update();
};