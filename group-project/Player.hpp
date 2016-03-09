#pragma once

/*
#include "Actor.hpp"

Data:
inventory vector


*/

#include "Actor.hpp"
#include "Vehicle.hpp"

class Player : public Actor
{
public:
	Player();
	~Player();

	int inVehicle = Config::VEH_FALSE;

	Vehicle* vehicle;

	void update(sf::Time);
	bool getDeath();
};