#pragma once

/*
instance of world object
*/

#include "SFML/Graphics.hpp"
#include "Updateable.hpp"
#include "Player.hpp"
#include "Zed.hpp"
#include "Config.hpp"

class Model
{
public:
	Model();
	~Model();

	std::vector<Updateable *> updatables;

	Player* player;
	Zed* zed;
	Zed* zed2;
	Zed* zed3;
	Zed* zed4;

	int** worldData;
	int worldCols, worldRows;

	void update(sf::Time);
};