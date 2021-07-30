#include "Bat.h"
#include "Ball.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include "SFML/Graphics.hpp"

using namespace sf;

int main()
{
    int windowWidth = 1024;
    int windowHeight = 768;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "iD Pong");
    window.setVerticalSyncEnabled(true);

    Bat bat(windowWidth / 2, windowHeight - 20);
    Ball ball(windowWidth / 2, 1);
    int scoreCache = 0;

    sf::Font font;
    sf::Text scoreText;
    font.loadFromFile("Candal.ttf");
    scoreText.setFont(font);
    scoreText.setPosition(412, 50);
    scoreText.setCharacterSize(50);
    scoreText.setString("Score: " + std::to_string(ball.getScore()));
    scoreText.setFillColor(sf::Color::Blue);

    sf::Text lifeCountText;
    lifeCountText.setFont(font);
    lifeCountText.setPosition(412, 20);
    lifeCountText.setCharacterSize(50);
    lifeCountText.setString("Lives: " + std::to_string(ball.getLifeCount()));
    lifeCountText.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            bat.moveLeft();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            bat.moveRight();
        }

        // Ball hit the top of the window
        if (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();
        }

        // Ball hit the bottom of the window
        if (ball.getPosition().top > windowHeight)
        {
            ball.decrementLifeCount();
            if (ball.getLifeCount() == 0)
            {
                ball.resetScore();
                ball.resetLifeCount();
                scoreText.setString("Score: " + std::to_string(ball.getScore()));
            }
            lifeCountText.setString("Lives: " + std::to_string(ball.getLifeCount()));
            ball.hitBottom();
        }

        // Ball hits the sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
        {
            ball.reboundSides();
        }

        // Ball hit the bat
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            ball.incrementScore();
            if (ball.getScore() == (scoreCache + 10) && bat.getShape().getSize().x > 50)
            {
                bat.decrementSize();
                scoreCache += 10;
            }
            ball.reboundBatOrTop();
            scoreText.setString("Score: " + std::to_string(ball.getScore()));
        }

        ball.update();
        bat.update();

        window.clear(Color(148, 213, 0, 255));
        window.draw(scoreText);
        window.draw(lifeCountText);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }
}