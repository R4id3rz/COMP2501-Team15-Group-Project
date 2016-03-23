#include "Key.hpp"

Key::Key(int x, int y, Vehicle* v) {
	position.x = x;
	position.y = y;
	vehicle = v;

	texture.loadFromFile(Config::KEY_IMAGE);
	texture.setSmooth(true);

	sprite.setTexture(texture); //init sprite
	sprite.setScale(0.5, 0.5);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

Vehicle* Key::getVehicle() {
	return vehicle;
}

void Key::setVehicle(Vehicle* v) {
	vehicle = v;
}