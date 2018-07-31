#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"


class Projectile{
private:
	sf::CircleShape projectile;
	sf::Vector2f playerPos;
public:
	Projectile();
	~Projectile();

	void setPosProjectiles(float, float);
	void shootProjectile();
	float getPosProjX();
	float getPosProjY();
	void drawProjectile(sf::RenderWindow&);
	sf::FloatRect GlobalBounds();

};