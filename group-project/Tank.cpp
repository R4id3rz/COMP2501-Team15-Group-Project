#include "Tank.hpp"

#include "Config.hpp"

Tank::Tank(float x, float  y)
	: Vehicle(TANKACCELERATION, TANKMAXSPEED, TANKTURNRATE, TANKFUEL) {
	position.x = x, position.y = y;
}

Tank::~Tank() {
}

void Tank::update(sf::Time time) {
	if (accel || decel || (speed != 0)) {				//Vehicle only turns when moving
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
		if (speed >(-maxSpeed / 2)) {
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