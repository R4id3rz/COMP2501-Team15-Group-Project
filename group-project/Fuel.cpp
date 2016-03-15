#include "Fuel.hpp"

Fuel::Fuel(int x, int y, int fuel) {
	position.x = x; //hardcoded init location
	position.y = y;

	//image.loadFromFile(Config::FUEL_IMAGE);
	//image.createMaskFromColor(sf::Color::White);
	//texture.loadFromImage(image);

	texture.loadFromFile(Config::FUEL_IMAGE);
	texture.setSmooth(true);

	sprite.setTexture(texture); //init sprite
	sprite.setScale(0.5, 0.5);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	fuelAmount = fuel;
}

int Fuel::getAmount() {
	return fuelAmount;
}

void Fuel::setAmount(int n) {
	fuelAmount = n;
}

sf::Vector2f Fuel::getPosition() {
	return position;
}

void Fuel::addFuel(int n) {
	fuelAmount += n;
}

void Fuel::removeFuel(int n) {
	fuelAmount -= n;
}