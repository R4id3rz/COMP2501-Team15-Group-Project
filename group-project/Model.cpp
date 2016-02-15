#include "Model.hpp"

Model::Model()
{
	//hardcoding and creating a player/zed and pushing to updatables
	player = new Player();
	zed = new Zed(player);
	this->updatables.push_back(player);
	this->updatables.push_back(zed);
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