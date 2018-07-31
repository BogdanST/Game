#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"

int main()
{

	//Window Render
	
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width/2)- 755, (sf::VideoMode::getDesktopMode().height/2)-390);
	window.create(sf::VideoMode(1500, 700), "My First Game", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);


	//Player
	Player myPlayer("..Textures/rocket.png");
	myPlayer.PosPlayer(window);
	//Projectilles
	Projectile projectile;
	std::vector<Projectile> projectiles;
	projectiles.push_back(projectile);
	int shootTimer = 0;


	Enemy enemy("..Textures/comet.png");
	std::vector<Enemy> enemies;
	enemies.push_back(enemy);
	int enemySpawnTimer = 0;

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

		if (shootTimer<30)
			shootTimer++;
		//Projectiles
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 30) {
			projectile.setPosProjectiles(myPlayer.getPlayerPosX() + 37.f, myPlayer.getPlayerPosY());
			projectiles.push_back(projectile);

			shootTimer = 0;
		}

		for (size_t i = 0; i < projectiles.size(); i++) {
			projectiles[i].shootProjectile();
			if (projectiles[i].getPosProjY() < 0)
				projectiles.erase(projectiles.begin() + i);
		}
		
		//ENEMIES
		if (enemySpawnTimer < 20) enemySpawnTimer++;
		if (enemySpawnTimer >= 20) {
			enemy.setEnemyPos(rand() % window.getSize().x, -200.f);
			enemies.push_back(enemy);
			enemySpawnTimer = 0;
		}
		for (size_t i = 0; i < enemies.size(); i++) {
			enemies[i].moveEnemy();
			if (enemies[i].getEnemyPosY() > window.getSize().y)
				enemies.erase(enemies.begin() + i);

		}
		
		
		for (size_t i = 0; i < projectiles.size(); ++i)
		{
			for (size_t k = 0; k < enemies.size(); ++k)
			{
				if (projectiles[i].GlobalBounds().intersects(enemies[k].GlobalBounds()))
				{
					projectiles.erase(projectiles.begin() + i);
					enemies.erase(enemies.begin() + k);
					break;
				}
			}

		}
	
		
		for (size_t i = 0; i < enemies.size(); ++i) {
			if (enemies[i].GlobalBounds().intersects(myPlayer.GlobalBounds())) {
				myPlayer.HealthDropped();
				if( myPlayer.health <= 0){
					
					std::cout << "You Lost!" << std::endl;
					
				}
				enemies.erase(enemies.begin() + i);
				
				break;
			}
		}
		
		window.clear();
		myPlayer.drawPlayer(window);
		for (size_t i = 0; i < enemies.size(); ++i) {
			enemies[i].drawEnemy(window);
		}
		for (size_t i = 0; i < projectiles.size(); ++i) {
			projectiles[i].drawProjectile(window);
		}
		window.display();
	}

	return 0;
}