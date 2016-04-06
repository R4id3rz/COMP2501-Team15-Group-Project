#include "Player.hpp"
#include <iostream>
//blah

Player::Player(float x, float y)
	: vehicle(0) {
	position.x = x; //hardcoded init location
	position.y = y;
	dead = false;

	image.loadFromFile(Config::PLAYER_IMAGE);
	image.createMaskFromColor(sf::Color::White);

	texture.setSmooth(true);
	texture.loadFromImage(image);

	sprite.setTexture(texture); //init sprite
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	inVehicle = Config::VEH_FALSE;

	fuel = new Fuel(0, 0, 0);
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
	return this->dead;
}

void Player::addFuel(int n) {
	fuel->addFuel(n);
}

int Player::getFuel() {
	return fuel->getAmount();
}

void Player::setFuel(int n)
{
	fuel->setAmount(n);
}

void Player::addKeys(int n) {
	numKeys += n;
}

void Player::removeKeys(int n) {
	if (numKeys >= n) {
		numKeys -= n;
	}
}

int Player::getNumKeys() {
	return numKeys;
}