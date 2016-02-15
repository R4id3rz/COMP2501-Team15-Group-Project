#pragma once
#include "Model.hpp"
#include "SFML/Graphics.hpp"
#include "Renderable.hpp"

class View
{
public:
	View(Model*);
	~View();

	sf::RenderWindow window;
	Model* model;

	int windowHeight = 900;
	int windowWidth = 1600;
	bool gameRunning = true;

	std::vector<Renderable *> renderables;

	void render();
};