#include "Tank.hpp"

#include "Config.hpp"

Tank::Tank(float x, float  y)
	: Vehicle(TANKACCELERATION, TANKMAXSPEED, TANKTURNRATE, TANKFUEL) {
	position.x = x, position.y = y;
	//image.loadFromFile(Config::TANK_IMAGE);
	//image.createMaskFromColor(sf::Color::White);
	//texture.loadFromImage(image);

	texture.loadFromFile(Config::TANK_IMAGE);
	texture.setSmooth(true);
	length = texture.getSize().x, width = texture.getSize().y;

	sprite.setTexture(texture); //init sprite
	sprite.setOrigin(22, texture.getSize().y / 2);
}

Tank::~Tank() {
}

void Tank::update(sf::Time time) {
	//   Keanu's code
	if (fuel > 0) {
		direction += delTurn;
		if (direction > 360) { direction -= 360; }
		else if (direction < 0) { direction += 360; }


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
			if (speed > 0) { speed -= acceleration*4; }
			else if (speed < 0) { speed += acceleration; }
		}
		if ((speed < acceleration) && (speed > -acceleration)) {//account for weird calculations stopping speed from ever reaching 0
			speed = 0;
		}

		if (speed != 0) {									//FUEL USAGE
			decreaseFuel(Config::MOVING_USAGE);
		}
		else {
			decreaseFuel(Config::IDLE_USAGE);
		}

		velocity.x = speed * cos(direction * PI / 180);		//This might be somewhat redundant.
		velocity.y = speed * sin(direction * PI / 180);
		position.x += velocity.x * time.asMilliseconds();
		position.y += velocity.y * time.asMilliseconds();
	}

	accel = decel = false;
	delTurn = 0;
}