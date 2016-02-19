#pragma once

/*
#include "Actor.hpp"

Data:
inventory vector


*/

#include "Actor.hpp"

class Player : public Actor
{
public:
	Player();
	~Player();

	int inVehicle = Config::VEH_FALSE;

	void update(sf::Time);
	bool getDeath();
};