#pragma once

/*
instance of world object
*/

#include "SFML/Graphics.hpp"
#include "Updateable.hpp"
#include "Player.hpp"
#include "Zed.hpp"
#include "Tank.hpp"
#include "Car.hpp"
#include "Truck.hpp"
#include "Config.hpp"

class Model
{
public:
	Model();
	~Model();

	std::vector<Actor *> updatables;

	Player* player;
	Zed* zed;
	Zed* zed2;
	Zed* zed3;
	Zed* zed4;
	std::vector<Vehicle*> vehicles;

	int** worldData;
	int worldCols, worldRows;

	void update(sf::Time);
};