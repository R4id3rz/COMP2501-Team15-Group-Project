#include "Zed.hpp"

Zed::Zed(Player* player) //accepts a player pointer to check its velocity
{
	position.x = 1200; //hardcoded init location
	position.y = 450;

	image.loadFromFile("EnemySlime.png");
	image.createMaskFromColor(sf::Color::White);

	textures.push_back(sf::Texture()); //crude system for having different textures for animation purposes (only 1 frame atm)
	textures.back().setSmooth(true);
	textures.back().loadFromImage(image);

	sprite.setTexture(textures.back()); //init sprite
	sprite.setOrigin(textures.back().getSize().x / 2, textures.back().getSize().y);

	this->player = player;
}

Zed::~Zed()
{}

void Zed::update(sf::Time time) //updates Zed velocity according to player, will overhaul this later...
{
	//chasing AI v2.0, normalizes the difference between the two positions as a vector (not my code)
	sf::Vector2f direction = player->position - this->position;
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.x = direction.x / length;
	direction.y = direction.y / length;

	position.x += direction.x * 0.1 * time.asMilliseconds();  //updates position using direction, speed and time, independant of FPS
	position.y += direction.y * 0.1 * time.asMilliseconds();

	//rotates the enemy sprite accordingly (not my code)
	float angle = atan2(player->position.y - this->position.y, player->position.x - this->position.x) * 180 / 3.141;
	sprite.setRotation(angle);
	
	sprite.setPosition(position);  //sets sprite location
}