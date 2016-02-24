#include "Truck.hpp"

#include "Config.hpp"

Truck::Truck(float x, float y) 
	: Vehicle(TRUCKACCELERATION, TRUCKMAXSPEED, TRUCKTURNRATE, TRUCKFUEL) {
	position.x = x, position.y = y;
}

Truck::~Truck() { }