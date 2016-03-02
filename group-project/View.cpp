#include "View.hpp"

#include <iostream>

View::View(Model* model)
	: winRows(10), winCols(16), tileRows(11), tileCols(17)
{
	this->model = model;
	this->window.create(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "COMP2501 Group Project");
	this->window.setFramerateLimit(Config::FPS);

	//hardcoding and pushing a player/zed model to be rendered
	//renderables.push_back(model->player);
	renderables.push_back(model->zed);
	renderables.push_back(model->zed2);
	renderables.push_back(model->zed3);
	renderables.push_back(model->zed4);

	//temp font indicator
	font.loadFromFile("arial.ttf");
	playerDead.setString("Player Died. Press C to Revive.");
	playerDead.setFont(font);
	playerDead.setStyle(sf::Text::Bold);
	playerDead.setPosition(800, 880);
	playerDead.setCharacterSize(20);
	playerDead.setColor(sf::Color::White);

	//Initialize VertexArray
	this->worldSprites.loadFromFile("spritesheet.png");
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
	updateView();
	std::cout << "P Pos: (" << model->player->position.x << ", " << model->player->position.y << ")" << std::endl;

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

	this->window.draw(model->player->sprite);
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
			wX = floor((pX - ((tileCols)*TILESIZE / 2)) / TILESIZE) + i;
			wY = floor((pY - ((tileRows)*TILESIZE / 2)) / TILESIZE) + j;
			tileNum = Grass;																//default tile to draw is grass
			if ((wX >= 0 && wY >= 0) && (wX < model->worldCols && wY < model->worldRows)) {	//avoid index out of bounds
				tileNum = model->worldData[wY][wX];
			}

			//SET POSITION OF CURRENT QUAD
			sf::Vertex* quad = &worldQuads[(i + j * tileCols) * 4];
			sX = -(pX - (floor(pX / TILESIZE))*TILESIZE) /*- (tileCols - winCols)*TILESIZE / 2*/ + (i*TILESIZE);
			sY = -(pY - (floor(pY / TILESIZE))*TILESIZE) /*- (tileRows - winRows)*TILESIZE / 2*/ + (j*TILESIZE);
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