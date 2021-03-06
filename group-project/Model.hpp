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


	std::vector<Key*>  keys;
	std::vector<Vehicle*> vehicles;
	std::vector<Fuel*> fuels;

	sf::Vector2f startPosition;
	sf::Vector2f endPosition;
	double distanceToGoal;

	int winningScore;
	sf::Time winningTime;

	int score;

	sf::Clock clock;
	sf::Time time;

	bool gameOver;

	int** worldData;
	int worldCols, worldRows, zScore;

	void update(sf::Time);
	void terrainBump(Actor*);											//Actor terrain collision
	void terrainBump(Vehicle*);											//Vehicle ditto
	void mapBump(Actor*);												//Actor world entrapment
	void mapBump(Vehicle*);												//Vehicle world entrapment
	sf::Vector2f closestCirclePoint(sf::Vector2f, sf::Vector2f, float);	//returns point input float distance from second vector towards first vector
	bool vehZedCollides(Vehicle*, Zed*);								//returns true if z->sprite->position is in contact w/ v->sprite
};