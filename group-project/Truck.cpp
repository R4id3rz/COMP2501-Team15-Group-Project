#include "Truck.hpp"

#include "Config.hpp"

Truck::Truck(float x, float y) 
	: Vehicle(TRUCKACCELERATION, TRUCKMAXSPEED, TRUCKTURNRATE, TRUCKFUEL) {
	position.x = x, position.y = y;
	length = 40, width = 16;
	texture.loadFromFile(Config::TRUCK_IMAGE);
	texture.setSmooth(true);

	sprite.setScale((float)length / texture.getSize().x, (float)width / texture.getSize().y);
	sprite.setTexture(texture); //init sprite
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

Truck::~Truck() { }