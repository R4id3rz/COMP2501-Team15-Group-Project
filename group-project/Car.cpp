#include "Car.hpp"

#include "Config.hpp"
#include <iostream>

Car::Car(float x, float y)
	: Vehicle(CARACCELERATION, CARMAXSPEED, CARTURNRATE, CARFUEL) {
	position.x = x, position.y = y;
	length = 32;
	width = 16;
	//image.loadFromFile(Config::CAR_IMAGE);
	//image.createMaskFromColor(sf::Color::White);
	//texture.loadFromImage(image);

	texture.loadFromFile(Config::CAR_IMAGE);
	float lScale = (float)length / (int)texture.getSize().x;
	float wScale = (float)width / (int)texture.getSize().y;
	sprite.setTexture(texture); //init sprite
	texture.setSmooth(true);
	sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
	sprite.setScale(lScale, wScale);
	
}

Car::~Car() {
}