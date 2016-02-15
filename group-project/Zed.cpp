#include "Zed.hpp"

Zed::Zed(Player* player) //accepts a player pointer to check its velocity
{
	position.x = 1200;
	position.y = 450;
	textures.push_back(sf::Texture());
	textures.back().setSmooth(true);
	textures.back().loadFromFile("EnemySlime.png");
	sprite.setTexture(textures.back());
	sprite.setOrigin(textures.back().getSize().x / 2, textures.back().getSize().y);

	this->player = player;
}

Zed::~Zed()
{}

void Zed::update(sf::Time time)
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

	position.x += velocity.x * time.asMilliseconds();
	position.y += velocity.y * time.asMilliseconds();

	sprite.setPosition(position);
}