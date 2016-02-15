#pragma once

/*
#include "Actor.hpp"

data:


*/

#include "Actor.hpp"
#include "Player.hpp"

class Zed : public Actor
{
public:
	Zed(Player*);
	~Zed();

	Player* player;

	void update(sf::Time);
};