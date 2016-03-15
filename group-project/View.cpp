#include "View.hpp"

#include <iostream>
#include <math.h>

View::View(Model* model)
	: winRows(10), winCols(16), tileRows(winRows+1), tileCols(winCols+1)
{
	this->model = model;
	this->window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "COMP2501 Group Project");
	this->window.setFramerateLimit(Config::FPS);

	//vehicles
	for (int i = 0; i < model->vehicles.size(); i++)
	{
		renderables.push_back(model->vehicles[i]);
	}
	//fuel
	for (int i = 0; i < model->fuels.size(); i++)
	{
		renderables.push_back(model->fuels[i]);
	}
	//updatables (zeds)
	for (int i = 0; i < model->updatables.size(); i++) {
		renderables.push_back(model->updatables[i]);
	}

	//temp font indicator
	font.loadFromFile("Assets/arial.ttf");
	playerDead.setString("Player Died. Press C to Revive.");
	playerDead.setFont(font);
	playerDead.setStyle(sf::Text::Bold);
	playerDead.setPosition(Config::WINDOW_WIDTH*1/4, Config::WINDOW_HEIGHT*3/4);
	playerDead.setCharacterSize(20);
	playerDead.setColor(sf::Color::Red);

	inVehicle.setString("Q to Enter Vehicle, E to Exit Vehicle");
	inVehicle.setFont(font);
	inVehicle.setStyle(sf::Text::Bold);
	inVehicle.setPosition(Config::WINDOW_WIDTH * 1 / 2.5, Config::WINDOW_HEIGHT * 4 / 5);
	inVehicle.setCharacterSize(20);
	inVehicle.setColor(sf::Color::Red);

	playerFuel.setString("Player Fuel: ");
	playerFuel.setFont(font);
	playerFuel.setStyle(sf::Text::Bold);
	playerFuel.setPosition(Config::WINDOW_WIDTH * 1 / 2.5, Config::WINDOW_HEIGHT * 4/6);
	playerFuel.setCharacterSize(20);
	playerFuel.setColor(sf::Color::Red);

	VehFuel.setString("Fuel: ");
	VehFuel.setFont(font);
	VehFuel.setStyle(sf::Text::Bold);
	VehFuel.setPosition(Config::WINDOW_WIDTH * 1 / 2.5, Config::WINDOW_HEIGHT * 5/6);
	VehFuel.setCharacterSize(20);
	VehFuel.setColor(sf::Color::Red);

	//Initialize VertexArray
	this->worldSprites.loadFromFile("Assets/spritesheet.png");
	this->states.texture = &worldSprites;

	this->worldQuads.setPrimitiveType(sf::Quads);
	this->worldQuads.resize(tileCols * tileRows * 4);

	tileCoords[Tree] = sf::Vector2f(384, 128);
	tileCoords[Grass] = tileCoords[zGrass] = tileCoords[Start] = tileCoords[End] = sf::Vector2f(384, 192);
	tileCoords[vRoad] = tileCoords[zvRoad] = sf::Vector2f(384, 0);
	tileCoords[hRoad] = tileCoords[zhRoad] = sf::Vector2f(256, 192);
	tileCoords[neRoad] = tileCoords[zneRoad] = sf::Vector2f(384, 64);
	tileCoords[esRoad] = tileCoords[zesRoad] = sf::Vector2f(0, 0);
	tileCoords[swRoad] = tileCoords[zswRoad] = sf::Vector2f(128, 128);
	tileCoords[wnRoad] = tileCoords[zwnRoad] = sf::Vector2f(448, 0);

	model->player->sprite.setPosition(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT /2);
}

View::~View()
{}

void View::render()
{
	//Update sprites
	updateView();
	
	std::cout << "P Pos: (" << model->player->position.x << ", " << model->player->position.y << ")" << std::endl;

	for (int i = 0; i < renderables.size(); i++) {		//Updates positions of sprites in renderables[n] relative to the player's sprite's position
		if (model->player->inVehicle == Config::VEH_FALSE)
			renderables[i]->sprite.setPosition(model->player->sprite.getPosition()+renderables[i]->position - model->player->position);
		else
			renderables[i]->sprite.setPosition(model->player->vehicle->sprite.getPosition() + renderables[i]->position - model->player->vehicle->position);
	}
	//Draw sprites
	this->window.clear();
	this->window.draw(worldQuads, states);
	for (int i = 0; i < this->renderables.size(); i++) //loops through entire renderable array and renders their sprites
	{
		this->window.draw(renderables[i]->sprite);
	}
	//temp display
	if (model->player->getDeath())
	{
		window.draw(playerDead);
	}
	
	if (model->player->vehicle == 0)//inVehicle == Config::VEH_FALSE) //not in vehicle, draw player
	{
		this->window.draw(model->player->sprite);
	}
	else //in vehicle, draw vehicle
	{
		model->player->vehicle->sprite.setPosition(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2);
		model->player->vehicle->sprite.setRotation(model->player->vehicle->getDirection());
		this->window.draw(model->player->vehicle->sprite);
		VehFuel.setString("Fuel: " + std::to_string(model->player->vehicle->getFuel()));
		this->window.draw(VehFuel);
	}
	window.draw(inVehicle);
	playerFuel.setString("Player Fuel: " + std::to_string(model->player->getFuel()));
	this->window.draw(playerFuel);
	
	this->window.display();
}

void View::updateView() {	//Update the VertexArray here
	float pX, pY, sX, sY;				//p = player's position (in world), s = current tile's position (in window)
	int wX, wY, tileNum;				//w = world tile corresponding to current tile, tileNum = worldData of current tile
		
	pX = model->player->position.x;
	pY = model->player->position.y;

	for (int i = 0; i < tileCols; i++) {
		for (int j = 0; j < tileRows; j++) {
			//GET CURRENT TILE WORLD TILE
			wX = floor((pX - ((winCols)*TILESIZE / 2)) / TILESIZE) + i;
			wY = floor((pY - ((winRows)*TILESIZE / 2)) / TILESIZE) + j;
			tileNum = Grass;																//default tile to draw is grass
			if ((wX >= 0 && wY >= 0) && (wX < model->worldCols && wY < model->worldRows)) {	//avoid index out of bounds
				tileNum = model->worldData[wY][wX];
			}

			//SET POSITION OF CURRENT QUAD
			sf::Vertex* quad = &worldQuads[(i + j * tileCols) * 4];
			sX = -(pX - (floor(pX / TILESIZE))*TILESIZE) + (i*TILESIZE);
			sY = -(pY - (floor(pY / TILESIZE))*TILESIZE) + (j*TILESIZE);
			quad[0].position = sf::Vector2f(sX, sY);
			quad[1].position = sf::Vector2f(sX + TILESIZE, sY);
			quad[2].position = sf::Vector2f(sX + TILESIZE, sY + TILESIZE);
			quad[3].position = sf::Vector2f(sX, sY + TILESIZE);

			//SET TEXTURE COORDINATE OF CURRENT QUAD
			quad[0].texCoords = tileCoords[tileNum];
			quad[1].texCoords = sf::Vector2f(tileCoords[tileNum].x+TILESIZE,tileCoords[tileNum].y);
			quad[2].texCoords = sf::Vector2f(tileCoords[tileNum].x+TILESIZE, tileCoords[tileNum].y+TILESIZE);
			quad[3].texCoords = sf::Vector2f(tileCoords[tileNum].x, tileCoords[tileNum].y+TILESIZE);
		}
	}
}