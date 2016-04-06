#include "Vehicle.hpp"
#include <math.h>

#define PI 3.1415926

Vehicle::Vehicle(float acceleration, float maxSpeed, float turnRate, int fuel)
	: acceleration(acceleration), maxSpeed(maxSpeed), turnRate(turnRate) {
	velocity.x = velocity.y = speed = delTurn = 0;
	direction = 0;
	accel = decel = false;
	locked = true;
	this->fuel = new Fuel(0, 0, fuel);
}

Vehicle::~Vehicle() { }

int Vehicle::getDirection()			{ return direction; }
sf::Vector2f Vehicle::getVelocity() { return velocity;  }
int Vehicle::getFuel()				{ return fuel->getAmount();	}

void Vehicle::setDirection(int angle) { direction = angle;  }

void Vehicle::decreaseFuel(int amount)
{ 
	if (fuel->getAmount() > 0)
		fuel->removeFuel(amount); 
	if (fuel->getAmount() < 0)
		fuel->setAmount(0);
}

void Vehicle::addFuel(int amount)
{
	fuel->addFuel(amount);
}

//void Vehicle::setVelocity(float x, float y)
//{
//	velocity.x = x;
//	velocity.y = y;
//}

void Vehicle::accelerate() {
	if (fuel->getAmount() > 0)
		accel = true;
}

void Vehicle::reverse() {
	if (fuel->getAmount() > 0)
		decel = true;
}

void Vehicle::turnLeft() {
	if (fuel->getAmount() > 0)
		delTurn = -1 * turnRate;
}

void Vehicle::turnRight() {
	if (fuel->getAmount() > 0)
		delTurn = turnRate;
}
void Vehicle::unlock() { locked = false; }
bool Vehicle::isLocked() { return locked; }

void Vehicle::update(sf::Time time) {
	if (!locked) {
		if (fuel > 0) {
			if (accel || decel || (speed != 0)) {				//Vehicle only turns when moving
				direction += delTurn;
				if (direction > 360) { direction -= 360; }
				else if (direction < 0) { direction += 360; }
				decreaseFuel(Config::MOVING_USAGE);
			}
			else {
				decreaseFuel(Config::IDLE_USAGE);
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
			if ((speed < acceleration) && (speed > -acceleration)) {//account for weird calculations stopping speed from ever reaching 0
				speed = 0;
			}

			velocity.x = speed * cos(direction * PI / 180) * time.asMilliseconds();		//This might be somewhat redundant.
			velocity.y = speed * sin(direction * PI / 180) * time.asMilliseconds();
			position.x += velocity.x;
			position.y += velocity.y;
		}
	}

	accel = decel = false;
	delTurn = 0;
}