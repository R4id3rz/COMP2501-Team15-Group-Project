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

	void update(sf::Time);
};