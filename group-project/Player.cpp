#include "Player.hpp"

Player::Player()
{
	position.x = 400; //hardcoded init location
	position.y = 450;

	image.loadFromFile("FriendlySlime.png");
	image.createMaskFromColor(sf::Color::White);

	textures.push_back(sf::Texture()); //crude system for having different textures for animation purposes (only 1 frame atm)
	textures.back().setSmooth(true);
	textures.back().loadFromImage(image);

	sprite.setTexture(textures.back()); //init sprite
	sprite.setOrigin(textures.back().getSize().x / 2, textures.back().getSize().y);
}

Player::~Player()
{}

void Player::update(sf::Time time)  //updates position using velocity and time, independant of FPS
{
	position.x += velocity.x * time.asMilliseconds();
	position.y += velocity.y * time.asMilliseconds();
	sprite.setPosition(position); //sets sprite location
}