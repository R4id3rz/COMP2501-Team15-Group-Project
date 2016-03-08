#include "Model.hpp"

#include <fstream>
#include <iostream>

Model::Model()
{
	//hardcoding and creating a player/zed and pushing to updatables
	player = new Player();
	zed = new Zed(player, 1200, 100);
	zed2 = new Zed(player, 1200, 200);
	zed3 = new Zed(player, 1200, 300);
	zed4 = new Zed(player, 1200, 400);
	this->vehicles.push_back(new Tank(500, 550));
	this->vehicles.push_back(new Tank(450, 550));
	this->vehicles.push_back(new Tank(500, 500));
	this->updatables.push_back(player);
	this->updatables.push_back(zed);
	this->updatables.push_back(zed2);
	this->updatables.push_back(zed3);
	this->updatables.push_back(zed4);
	for (int i = 0; i < this->vehicles.size(); i++)
	{
		this->updatables.push_back(vehicles[i]);
	}

	//Load world from file
	std::ifstream fileReader;
	fileReader.open("map.txt");
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
			if (worldData[i][j] < 10) {
				std::cout << "0" << worldData[i][j] << " ";
			}
			else { std::cout << worldData[i][j] << " "; }
		}
		std::cout << std::endl;
	}
}

Model::~Model()
{}

void Model::update(sf::Time deltaTime)
{
	for (int i = 0; i < this->updatables.size(); i++) //loops through updatables array and updates everything in it
	{
		updatables[i]->update(deltaTime);
	}
}