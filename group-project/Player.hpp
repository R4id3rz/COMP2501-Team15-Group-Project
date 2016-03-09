#pragma once

/*
#include "Actor.hpp"

Data:
inventory vector


*/

#include "Actor.hpp"
#include "Fuel.hpp"
#include "Key.hpp"

class Player : public Actor
{
public:
	Player();
	~Player();

	int inVehicle = Config::VEH_FALSE;

	void update(sf::Time);
	bool getDeath();

	void setFuel(int);
	int getFuel();

	void setKey(Key, int);
	Key getKey(int);
	Vehicle* vehicle;

private:
	Fuel fuel;
	Key keys[];
};