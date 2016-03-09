#include "Player.hpp"
#include <iostream>
//blah

Player::Player()
	: vehicle(0)  {
	position.x = Config::PLAYER_START_POS_X; //hardcoded init location
	position.y = Config::PLAYER_START_POS_Y;

	image.loadFromFile(Config::PLAYER_IMAGE);
	image.createMaskFromColor(sf::Color::White);

	texture.setSmooth(true);
	texture.loadFromImage(image);

	sprite.setTexture(texture); //init sprite
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	inVehicle = Config::VEH_FALSE;
}

Player::~Player()
{}

void Player::update(sf::Time time)  //updates position using velocity and time, independant of FPS
{
	if (inVehicle == Config::VEH_FALSE)
	{
		position.x += velocity.x * time.asMilliseconds();
		position.y += velocity.y * time.asMilliseconds();
	}
	else
	{
		position.x = vehicle->position.x;
		position.y = vehicle->position.y;
	}
}

bool Player::getDeath()
{
	return this->isDead;
}

void Player::setFuel(int n) {
	fuel.setAmount(n);
}

int Player::getFuel() {
	return fuel.getAmount();
}

Key Player::getKey(int n) {
	return keys[n];
}

void Player::setKey(Key k, int n) {
	keys[n] = k;
}