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

private:
	//World representation through VertexArray
	int winCols, winRows, tileCols, tileRows;
	sf::VertexArray worldQuads;
	sf::Texture worldSprites;
	sf::RenderStates states;

	void updateView();			//Update worldQuads
};