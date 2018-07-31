#include "Projectile.h"

Projectile::Projectile() {
	projectile.setFillColor(sf::Color::Blue);
	projectile.setRadius(5.0f);
}
Projectile::~Projectile(){}

void Projectile::setPosProjectiles(float x, float y) {
	projectile.setPosition(x, y);
}

void Projectile::shootProjectile() {
	projectile.move(0.f, -10.f);
}

float Projectile::getPosProjY() {
	float yaxis = projectile.getPosition().y;
	return yaxis;
}

float Projectile::getPosProjX() {
	float xaxis = projectile.getPosition().x;
	return xaxis;
}
void Projectile::drawProjectile(sf::RenderWindow& window) {
	window.draw(projectile);
}

sf::FloatRect Projectile::GlobalBounds() {
	return projectile.getGlobalBounds();
}