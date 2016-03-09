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
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < model->vehicles.size(); i++)
		{
			float distance = sqrt(std::pow(model->player->position.x - model->vehicles[i]->position.x, 2) + std::pow(model->player->position.y - model->vehicles[i]->position.y, 2));
			std::cout << distance << std::endl;
			if (distance < Config::VEH_ENTER_DISTANCE)
			{
				model->player->inVehicle = Config::VEH_TRUE;
				model->player->vehicle = model->vehicles[i];
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		model->player->inVehicle = Config::VEH_FALSE;
		model->player->vehicle = NULL;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		model->player->isDead = false;
	}

	if (model->player->inVehicle == Config::VEH_TRUE) //in vehicle
	{
		model->player->vehicle->decreaseFuel(Config::IDLE_USAGE);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))						//up arrow is pressed
		{
			model->player->vehicle->decreaseFuel(Config::MOVING_USAGE);
			float radAngle = model->player->vehicle->getDirection() * PI / 180; //computes vehicle's angle in radians
			float newX = 0 * std::cos(radAngle) - (-2) * std::sin(radAngle);	//rotates a velocity vector of (0,-5) to player's angle
			float newY = 0 * std::sin(radAngle) + (-2) * std::cos(radAngle);

			model->player->vehicle->setVelocity(newX,newY);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))				//down arrow is pressed
		{
			model->player->vehicle->decreaseFuel(Config::MOVING_USAGE);
			float radAngle = model->player->vehicle->getDirection() * PI / 180; //same as above, but with (0,5) vector
			float newX = 0 * std::cos(radAngle) - 2 * std::sin(radAngle);
			float newY = 0 * std::sin(radAngle) + 2 * std::cos(radAngle);

			model->player->vehicle->setVelocity(newX, newY);
		}
		else
		{
			model->player->vehicle->setVelocity(0, 0);							//resets velocity to 0 if nothing is pressed
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))						//left arrow
		{
			model->player->vehicle->decreaseFuel(Config::MOVING_USAGE);
			model->player->vehicle->setDirection((model->player->vehicle->getDirection() - 2) % 360);	//rotates vehicle angle
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))				//right arrow
		{
			model->player->vehicle->decreaseFuel(Config::MOVING_USAGE);
			model->player->vehicle->setDirection((model->player->vehicle->getDirection() + 2) % 360);	//rotates vehicle angle
		}
		
		/*    using Keanu's code.
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
		*/
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