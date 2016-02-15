#pragma once

/*
instance of world object
*/

#include "SFML/Graphics.hpp"
#include "Updateable.hpp"
#include "Player.hpp"
#include "Zed.hpp"

class Model
{
public:
	Model();
	~Model();

	std::vector<Updateable *> updatables;

	Player* player;
	Zed* zed;

	void update(sf::Time);
};