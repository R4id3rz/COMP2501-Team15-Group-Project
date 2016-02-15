#include "Zed.hpp"

Zed::Zed(Player* player) //accepts a player pointer to check its velocity
{
	position.x = 1200; //hardcoded init location
	position.y = 450;

	textures.push_back(sf::Texture()); //crude system for having different textures for animation purposes (only 1 frame atm)
	textures.back().setSmooth(true);
	textures.back().loadFromFile("EnemySlime.png");

	sprite.setTexture(textures.back()); //init sprite
	sprite.setOrigin(textures.back().getSize().x / 2, textures.back().getSize().y);

	this->player = player;
}

Zed::~Zed()
{}

void Zed::update(sf::Time time) //updates Zed velocity according to player, will overhaul this later...
{
	//player is....
	if (player->position.x < position.x && player->position.y < position.y) //top left
	{
		velocity.x = -0.05;
		velocity.y = -0.05;
	}
	else if (player->position.x > position.x && player->position.y < position.y) //top right
	{
		velocity.x = 0.05;
		velocity.y = -0.05;
	}
	else if (player->position.x < position.x && player->position.y > position.y) //bottom left
	{
		velocity.x = -0.05;
		velocity.y = 0.05;
	}
	else if (player->position.x > position.x && player->position.y > position.y) //bottom right
	{
		velocity.x = 0.05;
		velocity.y = 0.05;
	}
	else if (player->position.x < position.x) //left
	{
		velocity.x = -0.05;
		velocity.y = 0;
	}
	else if (player->position.x > position.x) //right
	{
		velocity.x = 0.05;
		velocity.y = 0;
	}
	else if (player->position.y < position.y) //top
	{
		velocity.x = 0;
		velocity.y = -0.05;
	}
	else if (player->position.y > position.y) //bottom
	{
		velocity.x = 0;
		velocity.y = 0.05;
	}
	else
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	position.x += velocity.x * time.asMilliseconds();  //updates position using velocity and time, independant of FPS
	position.y += velocity.y * time.asMilliseconds();

	sprite.setPosition(position);  //sets sprite location
}