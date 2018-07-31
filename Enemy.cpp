#include "Enemy.h"

Enemy::Enemy(std::string imgDir)
{
	this->damage = 20;
	if (!pTexture.loadFromFile(imgDir)) {
		std::cerr << "Error" << std::endl;
	}
	pSprite.setTexture(pTexture);
}
Enemy::~Enemy() {}


float Enemy::getEnemyPosX() {
	float xaxis = pSprite.getPosition().x;
	return xaxis;
}

float Enemy::getEnemyPosY() {
	float yaxis = pSprite.getPosition().y;
	return yaxis;
}

void Enemy::setEnemyPos(float x, float y) {
	pSprite.setPosition(sf::Vector2f(x,y));
}

void Enemy::moveEnemy() {
	pSprite.move(0.f, 5.f);
}

void Enemy::drawEnemy(sf::RenderWindow& window) {
	window.draw(pSprite);
}

sf::FloatRect Enemy::GlobalBounds() {
	return pSprite.getGlobalBounds();	
}

