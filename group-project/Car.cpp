#include "Car.hpp"

#include "Config.hpp"

Car::Car(float x, float y)
	: Vehicle(CARACCELERATION, CARMAXSPEED, CARTURNRATE, CARFUEL) {
	position.x = x, position.y = y;
}

Car::~Car() {
}