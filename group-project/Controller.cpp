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

	while (view->window.pollEvent(event)) //window close
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			view->window.close();
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		model->player->inVehicle = Config::VEH_TRUE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		model->player->inVehicle = Config::VEH_FALSE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		model->player->isDead = false;
	}

	//just dont question this... Its ugly but it works
	//goes into outer loop if a key is pressed, can add a boolean tag for "inVehicle" also, for triple nested
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{ //inner loop handles velocity changes
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
			sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //up + left case
		{
			model->player->velocity.x = 0; //set to 0 to fix bugs
			model->player->velocity.y = 0;
			model->player->velocity.x = -1 * Config::PLAYER_VELOCITY;  //backwards
			model->player->velocity.y = -1 * Config::PLAYER_VELOCITY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
				 sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //down + left case
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = 0;
			model->player->velocity.x = -1 * Config::PLAYER_VELOCITY;
			model->player->velocity.y = Config::PLAYER_VELOCITY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
				 sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //up + right case
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = 0;
			model->player->velocity.x = Config::PLAYER_VELOCITY;
			model->player->velocity.y = -1 * Config::PLAYER_VELOCITY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
				 sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //down + right case
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = 0;
			model->player->velocity.x = Config::PLAYER_VELOCITY;
			model->player->velocity.y = Config::PLAYER_VELOCITY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //up
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = -1 * Config::PLAYER_VELOCITY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //down
		{
			model->player->velocity.x = 0;
			model->player->velocity.y = Config::PLAYER_VELOCITY;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //left
		{
			model->player->velocity.x = -1 * Config::PLAYER_VELOCITY;
			model->player->velocity.y = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //right
		{
			model->player->velocity.x = Config::PLAYER_VELOCITY;
			model->player->velocity.y = 0;
		}
	}
	else  //no input, set velocity to 0
	{
		model->player->velocity.x = 0;
		model->player->velocity.y = 0;
	}
}