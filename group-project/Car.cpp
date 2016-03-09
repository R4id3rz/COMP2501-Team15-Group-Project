#include "Car.hpp"

#include "Config.hpp"

Car::Car(float x, float y)
	: Vehicle(CARACCELERATION, CARMAXSPEED, CARTURNRATE, CARFUEL) {
	position.x = x, position.y = y;

	image.loadFromFile(Config::CAR_IMAGE);
	image.createMaskFromColor(sf::Color::White);

	texture.setSmooth(true);
	texture.loadFromImage(image);

	sprite.setTexture(texture); //init sprite
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

Car::~Car() {
}