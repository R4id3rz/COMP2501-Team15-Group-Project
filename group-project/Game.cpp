#include "Game.hpp"

Game::Game()
{
	model = new Model();
	view = new View(model);
	controller = new Controller(model, view);
}

Game::~Game()
{}

void Game::loop()
{
	sf::Time deltaTime;
	while (view->window.isOpen())
	{
		deltaTime = this->clock.restart();
		
		controller->inputs();
		model->update(deltaTime);
		view->render();
	}
}