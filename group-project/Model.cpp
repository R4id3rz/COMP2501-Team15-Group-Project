#include "Model.hpp"

Model::Model()
{
	player = new Player();
	zed = new Zed(player);
	this->updatables.push_back(player);
	this->updatables.push_back(zed);
}

Model::~Model()
{}

void Model::update(sf::Time deltaTime)
{
	for (int i = 0; i < this->updatables.size(); i++)
	{
		updatables[i]->update(deltaTime);
	}
}