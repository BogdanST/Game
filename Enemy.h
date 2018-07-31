#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Projectile.h"

class Enemy
{
private:
	int damage;
	sf::Texture pTexture;
	sf::Sprite pSprite;

public:
	Enemy(std::string);
	~Enemy();
	
	float getEnemyPosX();
	float getEnemyPosY();
	void setEnemyPos(float,float);
	void moveEnemy();
	void drawEnemy(sf::RenderWindow&);
	sf::FloatRect GlobalBounds();
};

