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
#include "Fuel.hpp"
#include "Config.hpp"

class Model
{
public:
	Model();
	~Model();

	std::vector<Zed *> updatables;

	Player* player;
	Zed* zed;
	Zed* zed2;
	Zed* zed3;
	Zed* zed4;
	std::vector<Vehicle*> vehicles;
	std::vector<Fuel*> fuels;

	int** worldData;
	int worldCols, worldRows;

	void update(sf::Time);
};