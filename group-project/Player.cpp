#include "Player.hpp"

Player::Player()
{
	position.x = 400;
	position.y = 450;
	textures.push_back(sf::Texture());
	textures.back().setSmooth(true);
	textures.back().loadFromFile("FriendlySlime.png");
	sprite.setTexture(textures.back());
	sprite.setOrigin(textures.back().getSize().x / 2, textures.back().getSize().y);
}

Player::~Player()
{}

void Player::update(sf::Time time)
{
	position.x += velocity.x * time.asMilliseconds();
	position.y += velocity.y * time.asMilliseconds();
	sprite.setPosition(position);
}