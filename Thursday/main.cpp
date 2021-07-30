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
	window.setVerticalSyncEnabled(true);
	GameState currentState = GameState::Menu;

	sf::View camera(sf::Vector2f(500, 500), sf::Vector2f(1200, 800));
	camera.setSize(600, 450);
	window.setView(camera);

	sf::Texture mouse;
	mouse.loadFromFile("walk_cycle.png");
	sf::IntRect rect[] = { sf::IntRect(0, 0, 64, 64), sf::IntRect(64, 0, 64, 64), sf::IntRect(128, 0, 64, 64), sf::IntRect(192, 0, 64, 64),
	sf::IntRect(0, 64, 64, 64), sf::IntRect(64, 64, 64, 64), sf::IntRect(128, 64, 64, 64) };

	sf::Sprite lostArk;
	sf::Vector2f movement;
	lostArk.setTexture(mouse);
	lostArk.setOrigin(32, 32);
	lostArk.setPosition(200, 200);
	lostArk.setTextureRect(rect[0]);
	int imgCount = 0;
	bool up = false, left = false, down = false, right = false;

	sf::Clock clock;
	sf::Clock frameClock;

	sf::Font font;
	sf::Text text;
	font.loadFromFile("Candal.ttf");
	text.setFont(font);
	text.setString("Blah.");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Blue);

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
			movement.y = -4.0f;
		else if (down)
			movement.y = 4.0f;
		else
		{
			movement.y += -0.05f * movement.y;
		}
		if (left)
			movement.x = -4.0f;
		else if (right)
			movement.x = 4.0f;
		else
		{
			movement.x += -0.05f * movement.x;
		}

		text.move(4.0f, 0);
		if (text.getPosition().x > 1200)
			text.setPosition(-150, 0);
		lostArk.move(movement);

		{
			float timer = clock.getElapsedTime().asSeconds();
			if (timer > 0.1f)
			{
				imgCount = (imgCount + 1) % 7;
				clock.restart();
			}
			lostArk.setTextureRect(rect[imgCount]);
		}

		window.clear();
		window.draw(lostArk);
		if (currentState == GameState::GamePlay)
		{
			window.draw(text);
		}
		
		window.display();
	}
}