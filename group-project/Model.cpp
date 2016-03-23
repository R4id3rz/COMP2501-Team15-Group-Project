#include "Model.hpp"

#include <fstream>
#include <iostream>

Model::Model()
{
	//hardcoding and creating a player/zed
	//player = new Player();
	zed = new Zed(player, 1200, 100);
	zed2 = new Zed(player, 1200, 200);
	zed3 = new Zed(player, 1200, 300);
	zed4 = new Zed(player, 1200, 400);

	//init fuel *Spawn this randomly when init map*
	this->fuels.push_back(new Fuel(550, 500, Config::DEFAULT_FUEL));
	this->fuels.push_back(new Fuel(600, 500, Config::DEFAULT_FUEL));
	this->fuels.push_back(new Fuel(400, 400, Config::DEFAULT_FUEL));

	//init vehicles
	this->vehicles.push_back(new Tank(500, 550));
	this->vehicles.push_back(new Tank(450, 550));
	this->vehicles.push_back(new Tank(500, 500));
	this->vehicles.push_back(new Car(300, 300));
	this->vehicles.push_back(new Truck(300, 400));
	
	//push zeds to updatables
	this->updatables.push_back(zed);
	this->updatables.push_back(zed2);
	this->updatables.push_back(zed3);
	this->updatables.push_back(zed4);

	Car* car = new Car(400, 400);
	this->keys.push_back(new Key(1200, 450, car));
	this->keys.push_back(new Key(400, 60, car));
	this->keys.push_back(new Key(600, 600, car));
	this->keys.push_back(new Key(100, 900, car));
	this->keys.push_back(new Key(800, 200, car));

	//Load world from file
	std::ifstream fileReader;
	fileReader.open("Assets/map.txt");
	fileReader >> worldCols;
	fileReader >> worldRows;
	worldData = new int*[worldRows];
	std::cout << "World: (" << worldCols << ", " << worldRows << ")" << std::endl;
	for (int i = 0; i < worldRows; i++) {
		worldData[i] = new int[worldCols];
	}
	for (int i = 0; i < worldRows; i++) {		//Format: worldData[row][column]
		for (int j = 0; j < worldCols; j++) {
			fileReader >> worldData[i][j];
			
			if (worldData[i][j] >= zGrass && worldData[i][j] <= zwnRoad) {
				updatables.push_back(new Zed(player, j*TILESIZE+TILESIZE/2, i*TILESIZE+TILESIZE/2));
			}
			if (worldData[i][j] == Start) {
				player = new Player(j*TILESIZE + TILESIZE / 2, i*TILESIZE + TILESIZE / 2);
				startPosition.x = (j*TILESIZE + TILESIZE / 2);
				startPosition.y = (i*TILESIZE + TILESIZE / 2);
			}
			if (worldData[i][j] == End) {
				endPosition.x = (j*TILESIZE + TILESIZE / 2);
				endPosition.y = (i*TILESIZE + TILESIZE / 2);
			}
			
			if (worldData[i][j] < 10) {
				std::cout << "0" << worldData[i][j] << " ";
			}
			else { std::cout << worldData[i][j] << " "; }
		}
		std::cout << std::endl;
	}
	if (player == 0) {
		player = new Player(Config::PLAYER_START_POS_X, Config::PLAYER_START_POS_Y);
	}
	for (int i = 0; i < updatables.size(); i++) {
		updatables[i]->player = this->player;
	}

	clock.restart();
	score = Config::INIT_SCORE;
}

Model::~Model()
{}

void Model::update(sf::Time deltaTime)
{
	time = clock.getElapsedTime();
	if (score > 0)
		score--;

	player->update(deltaTime);
	for (int i = 0; i < this->updatables.size(); i++) //loops through updatables array and updates everything in it
	{
		updatables[i]->update(deltaTime);
		terrainBump(updatables[i]);
	}
	if (player->vehicle != 0) {
		player->vehicle->update(deltaTime);
		terrainBump(player->vehicle);
	}
	terrainBump(player);
	distanceToGoal = sqrt(std::pow(player->position.x - endPosition.x, 2) + std::pow(player->position.y - endPosition.y, 2));
	if (distanceToGoal < 20 && !gameOver)
	{
		gameOver = true;
		winningTime = time;
		winningScore = score;
	}
}
void Model::terrainBump(Actor* actor) {
	int tileX = floor(actor->position.x / TILESIZE);
	int tileY = floor(actor->position.y / TILESIZE);
	sf::Vector2f pos = sf::Vector2f(actor->position.x - tileX*TILESIZE, actor->position.y - tileY*TILESIZE);
	if (tileX >= 0 && tileX < worldCols && tileY >= 0 && tileY < worldRows) {
		if (worldData[tileY][tileX] == Tree) {
			if (pos.x <= pos.y) {
				if ((-pos.x + 64) <= pos.y) {		//actor is on south side of tile
					actor->position.y += TILESIZE - pos.y;
				}
				else if ((-pos.x + 64) >= pos.y) {	//actor is on west side of tile
					actor->position.x -= pos.x;
				}
			}
			else if (pos.x >= pos.y) {
				if ((-pos.x + 64) <= pos.y) {		//actor is on east side of tile
					actor->position.x += TILESIZE - pos.x;
				}
				else if ((-pos.x + 64) >= pos.y) {	//actor is on north side of tile
					actor->position.y -= pos.y;
				}
			}
		}
	}
}
void Model::terrainBump(Vehicle* actor) {
	int tileX = floor(actor->position.x / TILESIZE);
	int tileY = floor(actor->position.y / TILESIZE);
	sf::Vector2f pos = sf::Vector2f(actor->position.x - tileX*TILESIZE, actor->position.y - tileY*TILESIZE);
	if (tileX >= 0 && tileX < worldCols && tileY >= 0 && tileY < worldRows) {
		if (worldData[tileY][tileX] == Tree) {
			if (pos.x <= pos.y) {
				if ((-pos.x + 64) <= pos.y) {		//actor is on south side of tile
					actor->position.y += TILESIZE - pos.y;
				}
				else if ((-pos.x + 64) >= pos.y) {	//actor is on west side of tile
					actor->position.x -= pos.x;
				}
			}
			else if (pos.x >= pos.y) {
				if ((-pos.x + 64) <= pos.y) {		//actor is on east side of tile
					actor->position.x += TILESIZE - pos.x;
				}
				else if ((-pos.x + 64) >= pos.y) {	//actor is on north side of tile
					actor->position.y -= pos.y;
				}
			}
			actor->speed = 0;
		}
	}
}