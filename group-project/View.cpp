#include "View.hpp"

View::View(Model* model)
{
	this->model = model;
	this->window.create(sf::VideoMode(windowWidth, windowHeight), "COMP2501 Group Project");
	this->window.setFramerateLimit(60);
	renderables.push_back(model->player);
	renderables.push_back(model->zed);
}

View::~View()
{}

void View::render()
{
	this->window.clear();
	for (int i = 0; i < this->renderables.size(); i++)
	{
		this->window.draw(renderables[i]->sprite);
	}
	this->window.display();
}