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
	Player(float, float);
	~Player();

	int inVehicle = Config::VEH_FALSE;

	void update(sf::Time);
	bool getDeath();

	void addFuel(int);
	void setFuel(int);
	int getFuel();

	Vehicle* vehicle;
	int getNumKeys();
	void addKeys(int);
	void removeKeys(int);

private:
	int numKeys = 0;
	Fuel* fuel;
};