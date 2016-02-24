#include "Vehicle.hpp"
#include <math.h>

#define PI 3.1415926

Vehicle::Vehicle(float acceleration, float maxSpeed, float turnRate, int fuel)
	: acceleration(acceleration), maxSpeed(maxSpeed), turnRate(turnRate), fuel(fuel) {
	direction = speed = delTurn = 0;
	accel = decel = false;
}

float Vehicle::getDirection() { return direction; }

void Vehicle::accelerate() {
	accel = true;
}

void Vehicle::reverse() {
	decel = true;
}

void Vehicle::turnLeft() {
	delTurn = -1 * turnRate;
}

void Vehicle::turnRight() {
	delTurn = turnRate;
}

void Vehicle::update() {
	if (accel || decel || (speed != 0)) {				//Vehicle only turns when moving
														//Will override Tank subclass to allow turning while stationary.
		direction += delTurn;
		if (direction > 360) { direction -= 360; }
		else if (direction < 0) { direction += 360; }
	}

	if (accel) {										//I try to avoid dividing acceleration to make sure speed can get to zero
		if (speed < maxSpeed) {
			speed += acceleration;
		}
	}
	else if (decel) {
		if (speed > (-maxSpeed / 2)) {
			speed -= acceleration;
		}
	}
	else if (speed != 0) {
		if (speed > 0) { speed -= acceleration; }
		else if (speed < 0) { speed += acceleration; }
	}
	velocity.x = speed * cos(direction * PI / 180);		//This might be somewhat redundant.
	velocity.y = speed * sin(direction * PI / 180);
	position.x += velocity.x;
	position.y += velocity.y;

	accel = decel = false;
	delTurn = 0;
}