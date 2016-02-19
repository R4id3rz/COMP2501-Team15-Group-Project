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

	//temp font indicator
	font.loadFromFile("arial.ttf");
	playerDead.setString("Player Died. Press C to Revive.");
	playerDead.setFont(font);
	playerDead.setStyle(sf::Text::Bold);
	playerDead.setPosition(800, 880);
	playerDead.setCharacterSize(20);
	playerDead.setColor(sf::Color::White);
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

	//temp display
	if (model->player->getDeath())
	{
		window.draw(playerDead);
	}

	this->window.display();
}