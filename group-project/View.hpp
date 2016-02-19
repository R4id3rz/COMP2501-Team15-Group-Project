#pragma once

#include "SFML/Graphics.hpp"
#include "Model.hpp"
#include "Renderable.hpp"
#include "Config.hpp"

class View
{
public:
	View(Model*);
	~View();

	sf::RenderWindow window;
	Model* model;

	bool gameRunning = true;

	std::vector<Renderable *> renderables;

	void render();

	//temp string
	sf::Font font;
	sf::Text playerDead;
};