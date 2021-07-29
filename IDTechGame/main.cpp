#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState
{
	Menu = 0,
	GamePlay
};

int main()
{

	/*
	sf::CircleShape circle;
	sf::CircleShape eye1;
	sf::CircleShape eye2;

	circle.setRadius(70);
	circle.setPosition(150, 150);
	circle.setFillColor(sf::Color::Blue);
	eye1.setRadius(15);
	eye1.setPosition(160, 180);
	eye1.setFillColor(sf::Color::Red);
	eye2.setRadius(15);
	eye2.setPosition(240, 180);
	eye2.setFillColor(sf::Color::Yellow);
	*/

	sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML Works");
	GameState currentState = GameState::Menu;

	sf::View camera(sf::Vector2f(80, 80), sf::Vector2f(150, 150));
	camera.setSize(250, 250);

	sf::Texture playTex;
	playTex.loadFromFile("Space Assets/player_ship.png");

	sf::Font font;
	sf::Text text;
	font.loadFromFile("Candal.ttf");
	text.setFont(font);
	text.setString("Blah.");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Blue);

	sf::Sprite player;
	sf::Vector2f movement(0.0f, 0.0f);
	player.setTexture(playTex);
	player.setPosition(200.0f, 200.0f);
	player.setScale(1.5f, 1.5f);
	player.setOrigin(64, 64);

	bool up = false, left = false, down = false, right = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					up = true;
					break;
				case sf::Keyboard::A:
					left = true;
					break;
				case sf::Keyboard::S:
					down = true;
					break;
				case sf::Keyboard::D:
					right = true;
					break;
				case sf::Keyboard::Space:
					(currentState == GameState::Menu) ? currentState = GameState::GamePlay :
						currentState = GameState::Menu;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					up = false;
					break;
				case sf::Keyboard::A:
					left = false;
					break;
				case sf::Keyboard::S:
					down = false;
					break;
				case sf::Keyboard::D:
					right = false;
					break;
				}
			}
		}

		if (up)
			movement.y = -0.5f;
		else if (down)
			movement.y = 0.5f;
		else
		{
			movement.y += -0.005f * movement.y;
		}
		if (left)
			movement.x = -0.5f;
		else if (right)
			movement.x = 0.5f;
		else
		{
			movement.x += -0.005f * movement.x;
		}

		text.move(0.3f, 0);
		if (text.getPosition().x > 1200)
			text.setPosition(-150, 0);
		player.move(movement);

		window.clear();

		if (currentState == GameState::GamePlay)
		{
			window.draw(text);
			window.draw(player);
		}
		
		window.display();
	}
}