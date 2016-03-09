#include "Vehicle.hpp"
#include <math.h>

#define PI 3.1415926

Vehicle::Vehicle(float acceleration, float maxSpeed, float turnRate, int fuel)
	: acceleration(acceleration), maxSpeed(maxSpeed), turnRate(turnRate), fuel(fuel) {
	velocity.x = velocity.y = speed = delTurn = 0;
	direction = 0;
	accel = decel = false;
}

Vehicle::~Vehicle() { }

int Vehicle::getDirection()			{ return direction; }
sf::Vector2f Vehicle::getVelocity() { return velocity;  }
int Vehicle::getFuel()				{ return fuel;		}

void Vehicle::setDirection(int angle) { direction = angle;  }
void Vehicle::decreaseFuel(int amount)
{ 
	if (fuel > 0)
		fuel = fuel - amount; 
	if (fuel < 0)
		fuel = 0;
}

void Vehicle::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

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

void Vehicle::update(sf::Time time) {
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
	velocity.x = speed * cos(direction * PI / 180) * time.asMilliseconds();		//This might be somewhat redundant.
	velocity.y = speed * sin(direction * PI / 180) * time.asMilliseconds();
	position.x += velocity.x;
	position.y += velocity.y;

	accel = decel = false;
	delTurn = 0;
}