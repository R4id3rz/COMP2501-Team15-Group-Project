#include "Controller.hpp"

Controller::Controller(Model* model, View* view)
{
	this->model = model;
	this->view = view;
}

Controller::~Controller()
{}

void Controller::inputs()
{
	sf::Event event;

	while (view->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			view->window.close();
			break;
		}
	}

	//just dont question this... Its ugly but it works
	//goes into outer loop if a key is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{ //inner loop handles velocity changes
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //up + left case
		{
			model->player->velocity.x = 0; //set to 0 to fix bugs
			model->player->velocity.y = 0;
			model->player->velocity.x = -0.1;
			model->player->velocity.y = -0.1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = 0;
			model->player->velocity.x = -0.1;
			model->player->velocity.y = 0.1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = 0;
			model->player->velocity.x = 0.1;
			model->player->velocity.y = -0.1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = 0;
			model->player->velocity.x = 0.1;
			model->player->velocity.y = 0.1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = -0.1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = 0.1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			model->player->velocity.x = -0.1;
			model->player->velocity.y = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			model->player->velocity.x = 0.1;
			model->player->velocity.y = 0;
		}
	}
	else  //no input, set velocity to 0
	{
		model->player->velocity.x = 0;
		model->player->velocity.y = 0;
	}
}