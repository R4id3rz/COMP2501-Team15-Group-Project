#include "Controller.hpp"
#include <iostream>

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
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if (model->player->inVehicle == Config::VEH_FALSE)
		{
			for (int i = 0; i < model->vehicles.size(); i++)
			{
				float distance = sqrt(std::pow(model->player->position.x - model->vehicles[i]->position.x, 2) + std::pow(model->player->position.y - model->vehicles[i]->position.y, 2));
				std::cout << distance << std::endl;
				if (distance < Config::VEH_ENTER_DISTANCE)
				{
					//when going in vehicle, put all player fuel into vehicle
					model->player->inVehicle = Config::VEH_TRUE;
					model->player->vehicle = model->vehicles[i];
					int playerFuel = model->player->getFuel();
					model->player->vehicle->addFuel(playerFuel);
					model->player->setFuel(0);
				}
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if (model->player->inVehicle == Config::VEH_TRUE)
		{
			//remove all fuel from vehicle and put into player
			model->player->inVehicle = Config::VEH_FALSE;
			int vehFuel = model->player->vehicle->getFuel();
			model->player->addFuel(vehFuel);
			model->player->vehicle->decreaseFuel(vehFuel);
			model->player->vehicle = 0;
		}
	}

	//debug
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		model->player->isDead = false;
	}

	//fuel pickup
	for (int i = 0; i < model->fuels.size(); i++)
	{
		float distance = sqrt(std::pow(model->player->position.x - model->fuels[i]->position.x, 2) + std::pow(model->player->position.y - model->fuels[i]->position.y, 2));
		if (distance < Config::FUEL_PICKUP_DISTANCE)
		{
			//adds fuel amount to player, remove fuel from model & view renderables
			model->player->addFuel(model->fuels[i]->getAmount());
			//complicated removing from a vector without knowing position....
			view->renderables.erase(std::remove(view->renderables.begin(), view->renderables.end(), model->fuels[i]), view->renderables.end());
			model->fuels.erase(model->fuels.begin() + i);

		}
	}

	if (model->player->inVehicle == Config::VEH_TRUE) //in vehicle
	{
		//    using Keanu's code.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			model->player->vehicle->accelerate();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			model->player->vehicle->reverse();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			model->player->vehicle->turnLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			model->player->vehicle->turnRight();
		}
	}
	else //on foot
	{
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
}