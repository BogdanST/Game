#include "Player.h"

Player::Player(std::string imgDir) {
	if (!pTexture.loadFromFile(imgDir)) {
		std::cerr << "Error\n";
	}
	this->health = 100;
	pSprite.setTexture(pTexture);
}
Player::~Player() {}

void Player::PosPlayer(sf::RenderWindow& window) { //set the postion
	pSprite.setPosition(sf::Vector2f(window.getSize().x / 2 - 75, window.getSize().y - 320));
}

float Player::getPlayerPosX() {
	float xaxis = pSprite.getPosition().x;
	return xaxis;
}

float Player::getPlayerPosY() {
	float yaxis = pSprite.getPosition().y;
	return yaxis;
}

void Player::drawPlayer(sf::RenderWindow& window) {
	window.draw(pSprite);
}

void Player::movePlayer(char direction, float moveSpeed) {
	if (direction == 'w' || direction == 'W') { //up
		pSprite.move(0, -moveSpeed);
	}
	else if (direction == 's' || direction == 'S') { //down
		pSprite.move(0, moveSpeed);
	}
	else if (direction == 'a' || direction == 'A') {  //left
		pSprite.move(-moveSpeed, 0);
	}
	else if (direction == 'd' || direction == 'D') { //right
		pSprite.move(moveSpeed, 0);
	}
}

sf::FloatRect Player::GlobalBounds() {
	return pSprite.getGlobalBounds();
}

void Player::HealthDropped() {
	std::cout << "Current health: " << health << "\n";
	health -= 10;
}

