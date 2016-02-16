#include "Model.hpp"

Model::Model()
{
	//hardcoding and creating a player/zed and pushing to updatables
	player = new Player();
	zed = new Zed(player, 1200, 100);
	zed2 = new Zed(player, 1200, 200);
	zed3 = new Zed(player, 1200, 300);
	zed4 = new Zed(player, 1200, 400);
	this->updatables.push_back(player);
	this->updatables.push_back(zed);
	this->updatables.push_back(zed2);
	this->updatables.push_back(zed3);
	this->updatables.push_back(zed4);
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