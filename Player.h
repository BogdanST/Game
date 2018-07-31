#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
private:
	sf::Texture pTexture;
	sf::Sprite pSprite;
	sf::Vector2f pos;

public:
	int health;
	Player(std::string);
	~Player();

	void PosPlayer(sf::RenderWindow&);
	float getPlayerPosX();
	float getPlayerPosY();
	void drawPlayer(sf::RenderWindow&);
	void movePlayer(char, float);
	sf::FloatRect GlobalBounds();
	void HealthDropped();
};
