#include "View.hpp"

#include <iostream>
#include <math.h>

View::View(Model* model)
	: winRows(10), winCols(16), tileRows(winRows+1), tileCols(winCols+1)
{
	this->model = model;
	this->window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "COMP2501 Group Project");
	this->window.setFramerateLimit(Config::FPS);

	//updatables (zeds)
	for (int i = 0; i < model->updatables.size(); i++) {
		renderables.push_back(model->updatables[i]);
	}
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
	//Keys
	for (int i = 0; i < model->keys.size(); i++) {
		renderables.push_back(model->keys[i]);
	}

	//temp font indicator
	font.loadFromFile("Assets/arial.ttf");
	playerDead.setString("Player Died. Press C to Revive.");
	playerDead.setFont(font);
	playerDead.setStyle(sf::Text::Bold);
	playerDead.setPosition(Config::WINDOW_WIDTH*1/4, Config::WINDOW_HEIGHT*3/4);
	playerDead.setCharacterSize(20);
	playerDead.setColor(sf::Color::Red);

	inVehicle.setString("E to Enter/Exit Vehicle");
	inVehicle.setFont(font);
	inVehicle.setStyle(sf::Text::Bold);
	inVehicle.setPosition(Config::WINDOW_WIDTH * 1 / 2.5, Config::WINDOW_HEIGHT * 4 / 5);
	inVehicle.setCharacterSize(20);
	inVehicle.setColor(sf::Color::Red);

	playerFuel.setString("Player Fuel: ");
	playerFuel.setFont(font);
	playerFuel.setStyle(sf::Text::Bold);
	playerFuel.setPosition(Config::WINDOW_WIDTH * 1 / 2.5, Config::WINDOW_HEIGHT * 5/6 + 20);
	playerFuel.setCharacterSize(20);
	playerFuel.setColor(sf::Color::Red);

	vehFuel.setString("Fuel: ");
	vehFuel.setFont(font);
	vehFuel.setStyle(sf::Text::Bold);
	vehFuel.setPosition(Config::WINDOW_WIDTH * 1 / 2.5, Config::WINDOW_HEIGHT * 5/6 + 40);
	vehFuel.setCharacterSize(20);
	vehFuel.setColor(sf::Color::Red);

	Keys.setString("Keys: ");
	Keys.setFont(font);
	Keys.setStyle(sf::Text::Bold);
	Keys.setPosition(Config::WINDOW_WIDTH * 1 / 2.5, Config::WINDOW_HEIGHT * 5 / 6 + 60);
	Keys.setCharacterSize(20);
	Keys.setColor(sf::Color::Red);

	goalDistance.setString("Distance to Goal: ");
	goalDistance.setFont(font);
	goalDistance.setStyle(sf::Text::Bold);
	goalDistance.setPosition(Config::WINDOW_WIDTH * 1 / 2.5, Config::WINDOW_HEIGHT * 5 / 6);
	goalDistance.setCharacterSize(20);
	goalDistance.setColor(sf::Color::Red);

	score.setString("Score: ");
	score.setFont(font);
	score.setStyle(sf::Text::Bold);
	score.setPosition(10, 10);
	score.setCharacterSize(20);
	score.setColor(sf::Color::Red);

	timeElapsed.setString("Time Elapsed: ");
	timeElapsed.setFont(font);
	timeElapsed.setStyle(sf::Text::Bold);
	timeElapsed.setPosition(10, 30);
	timeElapsed.setCharacterSize(20);
	timeElapsed.setColor(sf::Color::Red);

	killCount.setString("Zombies killed: ");
	killCount.setFont(font);
	killCount.setStyle(sf::Text::Bold);
	killCount.setPosition(10, 50);
	killCount.setCharacterSize(20);
	killCount.setColor(sf::Color::Red);

	gameOver.setString("GAME OVER");
	gameOver.setFont(font);
	gameOver.setStyle(sf::Text::Bold);
	gameOver.setPosition(Config::WINDOW_WIDTH / 3, Config::WINDOW_HEIGHT / 3);
	gameOver.setCharacterSize(40);
	gameOver.setColor(sf::Color::Black);

	//Initialize VertexArray
	this->worldSprites.loadFromFile("Assets/spritesheet.png");
	this->states.texture = &worldSprites;

	this->worldQuads.setPrimitiveType(sf::Quads);
	this->worldQuads.resize(tileCols * tileRows * 4);

	tileCoords[Tree] = sf::Vector2f(384, 128);
	tileCoords[End] = sf::Vector2f(448, 128);
	tileCoords[Grass] = tileCoords[zGrass] = tileCoords[Start] = sf::Vector2f(384, 192);
	tileCoords[kSpawn] = tileCoords[fSpawn] = sf::Vector2f(384, 192);							//Item spawners (same as Grass)
	tileCoords[cSpawn] = tileCoords[tkSpawn] = tileCoords[tnSpawn] = sf::Vector2f(384, 192);	//Vehicle spawners (ditto)
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
	
	//std::cout << "P Pos: (" << model->player->position.x << ", " << model->player->position.y << ")" << std::endl;

	for (int i = 0; i < renderables.size(); i++) {		//Updates positions of sprites in renderables[n] relative to the player's sprite's position
		//if (model->player->inVehicle == Config::VEH_FALSE)
			renderables[i]->sprite.setPosition(model->player->sprite.getPosition()+renderables[i]->position - model->player->position);
		//else
		//	renderables[i]->sprite.setPosition(model->player->vehicle->sprite.getPosition() + renderables[i]->position - model->player->vehicle->position);
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
		//model->player->vehicle->sprite.setPosition(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2);
		model->player->vehicle->sprite.setRotation(model->player->vehicle->getDirection());
		//this->window.draw(model->player->vehicle->sprite);
		vehFuel.setString("Fuel: " + std::to_string(model->player->vehicle->getFuel()) + "L");
		this->window.draw(vehFuel);
	}

	//drawing all the various texts
	window.draw(inVehicle);
	playerFuel.setString("Player Fuel: " + std::to_string(model->player->getFuel()) + "L");
	window.draw(playerFuel);
	Keys.setString("Player Keys: " + std::to_string(model->player->getNumKeys()));
	window.draw(Keys);
	goalDistance.setString("Distance to Goal: " + std::to_string((int)model->distanceToGoal) + "m");
	window.draw(goalDistance);
	score.setString("Score: " + std::to_string(model->score));
	window.draw(score);
	std::string seconds = std::to_string((int)model->time.asSeconds() % 60);
	std::string minutes = std::to_string(model->time.asSeconds() / 60);
	//adds a 0 in front of the second
	if (((int)model->time.asSeconds() % 60) < 10)
		seconds = "0" + std::to_string((int)model->time.asSeconds() % 60);
	if ((model->time.asSeconds() / 60) < 10)
		minutes = "0" + std::to_string((int)model->time.asSeconds() / 60);
	timeElapsed.setString("Time Elapsed: " + minutes + ":" + seconds);
	window.draw(timeElapsed);
	killCount.setString("Zombies killed: " + std::to_string(model->zScore));
	window.draw(killCount);
	if (model->gameOver)
	{
		std::string seconds = std::to_string((int)model->winningTime.asSeconds() % 60);
		std::string minutes = std::to_string(model->winningTime.asSeconds() / 60);
		//adds a 0 in front of the second
		if (((int)model->time.asSeconds() % 60) < 10)
			seconds = "0" + std::to_string((int)model->winningTime.asSeconds() % 60);
		if ((model->time.asSeconds() / 60) < 10)
			minutes = "0" + std::to_string((int)model->winningTime.asSeconds() / 60);
		gameOver.setString("    GAME OVER\n Final Score: " + std::to_string(model->winningScore) + "\n Final Time: " + minutes + ":" + seconds);
		window.draw(gameOver);
	}


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
			tileNum = Tree;																	//default tile to draw is tree
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