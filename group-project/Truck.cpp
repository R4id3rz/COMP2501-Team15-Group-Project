#include "Truck.hpp"

#include "Config.hpp"

Truck::Truck(float x, float y) 
	: Vehicle(TRUCKACCELERATION, TRUCKMAXSPEED, TRUCKTURNRATE, TRUCKFUEL) {
	position.x = x, position.y = y;

	texture.loadFromFile(Config::TRUCK_IMAGE);
	texture.setSmooth(true);

	sprite.setTexture(texture); //init sprite
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

Truck::~Truck() { }