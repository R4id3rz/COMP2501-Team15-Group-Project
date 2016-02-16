#include "View.hpp"

View::View(Model* model)
{
	this->model = model;
	this->window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "COMP2501 Group Project");
	this->window.setFramerateLimit(Config::FPS);

	//hardcoding and pushing a player/zed model to be rendered
	renderables.push_back(model->player);
	renderables.push_back(model->zed);
	renderables.push_back(model->zed2);
	renderables.push_back(model->zed3);
	renderables.push_back(model->zed4);
}

View::~View()
{}

void View::render()
{
	this->window.clear();
	for (int i = 0; i < this->renderables.size(); i++) //loops through entire renderable array and renders their sprites
	{
		this->window.draw(renderables[i]->sprite);
	}
	this->window.display();
}