#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Player.h"

int main()
{
	srand(time(NULL));
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 755, (sf::VideoMode::getDesktopMode().height / 2) - 390);
	window.create(sf::VideoMode(1500, 700), "My First Game", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);


	Player myPlayer("rocket.png");

	sf::CircleShape projectile;
	projectile.setFillColor(sf::Color::Red);
	projectile.setRadius(5.f);

	sf::CircleShape player;
	int playerhealth = 100;
	player.setFillColor(sf::Color::White);
	player.setRadius(50.f);
	player.setPosition(window.getSize().x / 2 - player.getRadius(), window.getSize().y - player.getRadius() * 2 - 10.f);


	sf::Vector2f playerCenter;
	int shootTimer = 0;
	std::vector<sf::CircleShape> projectiles;
	projectiles.push_back(sf::CircleShape(projectile));


	sf::RectangleShape enemy;
	enemy.setFillColor(sf::Color::Magenta);
	enemy.setSize(sf::Vector2f(50.f, 50.f));

	std::vector<sf::RectangleShape> enemies;
	enemies.push_back(sf::RectangleShape(enemy));
	int enemySpawnTimer = 0;


	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				myPlayer.movePlayer('w', 12.0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				myPlayer.movePlayer('s', 12.0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				myPlayer.movePlayer('a', 12.0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				myPlayer.movePlayer('d', 12.0);
			}
		}

		//UPDATE:
		//PLAYER
		playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());

		player.setPosition(sf::Mouse::getPosition(window).x, player.getPosition().y);

		if (shootTimer<5)
			shootTimer++;
		//Projectiles
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 3) {
			projectile.setPosition(playerCenter);
			projectiles.push_back(sf::CircleShape(projectile));

			shootTimer = 0;
		}

		for (size_t i = 0; i < projectiles.size(); i++) {
			projectiles[i].move(0.f, -10.f);
			if (projectiles[i].getPosition().y < 0)
				projectiles.erase(projectiles.begin() + i);

		}
		//ENEMIES
		if (enemySpawnTimer < 20) enemySpawnTimer++;
		if (enemySpawnTimer >= 20) {
			enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0.f);
			enemies.push_back(sf::RectangleShape(enemy));
			enemySpawnTimer = 0;
		}
		for (size_t i = 0; i < enemies.size(); i++) {
			enemies[i].move(0.f, 5.f);
			if (enemies[i].getPosition().y > window.getSize().y)
				enemies.erase(enemies.begin() + i);

		}

		//COLLISION - PROjectile with ENEMY~
		for (size_t i = 0; i < projectiles.size(); ++i)
		{
			for (size_t k = 0; k < enemies.size(); ++k)
			{
				if (projectiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
				{
					projectiles.erase(projectiles.begin() + i);
					enemies.erase(enemies.begin() + k);
					break;
				}
			}

		}


		//COLLISON - Enemy with Player

		for (size_t i = 0; i < enemies.size(); ++i) {
			if (enemies[i].getGlobalBounds().intersects(player.getGlobalBounds())) {
				if (playerhealth <= 0) {

					std::cout << "You Lost!" << std::endl;

				}
				enemies.erase(enemies.begin() + i);

				playerhealth -= 10;

				break;
			}
		}



		window.clear();
		window.draw(player);
		myPlayer.drawPlayer(window);


		for (size_t i = 0; i < enemies.size(); ++i) {
			window.draw(enemies[i]);
		}

		for (size_t i = 0; i < projectiles.size(); ++i) {
			window.draw(projectiles[i]);
		}


		window.display();
	}

	return 0;
}
