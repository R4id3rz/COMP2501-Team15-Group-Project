#pragma once

#include "SFML/Graphics.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include "Config.hpp"

class Game
{
public:
	Game();
	~Game();

	Model* model;
	View* view;
	Controller* controller;
	sf::Clock clock;

	void loop();
};