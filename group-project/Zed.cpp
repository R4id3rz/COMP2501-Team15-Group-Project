#include "Zed.hpp"

Zed::Zed(Player* player, int x, int y) //accepts a player pointer to check its velocity
{
	position.x = x; //hardcoded init location
	position.y = y;
	dead = false;

	//image.loadFromFile(Config::TANK_IMAGE);
	//image.createMaskFromColor(sf::Color::White);
	//texture.loadFromImage(image);

	texture.loadFromFile(Config::ZED_IMAGE);
	texture.setSmooth(true);

	sprite.setTexture(texture); //init sprite
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	this->player = player;
}

Zed::~Zed()
{}

void Zed::update(sf::Time time) //updates Zed velocity according to player, will overhaul this later...
{
	if (!dead) {
		float distance = sqrt(std::pow(player->position.x - this->position.x, 2) + std::pow(player->position.y - this->position.y, 2));
		if (distance < Config::ZED_KILL_DISTANCE && player->inVehicle == Config::VEH_FALSE)
		{
			player->kill();
		}
		else if (distance < Config::ZED_FOLLOW_DISTANCE) //only follows if within a certain distance
		{
			//chasing AI v2.0, normalizes the difference between the two positions as a vector (not my code)
			sf::Vector2f direction = player->position - this->position;
			float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			direction.x = direction.x / length;
			direction.y = direction.y / length;

			position.x += direction.x * Config::ZED_VELOCITY * time.asMilliseconds() * player->inVehicle;  //updates position using direction, speed and time, independant of FPS
			position.y += direction.y * Config::ZED_VELOCITY * time.asMilliseconds() * player->inVehicle;  //inVehicle changes the speed to negative, aka running away

			//rotates the enemy sprite accordingly (not my code), needs bug fixing
			float angle = atan2(this->position.y - player->position.y, this->position.x - player->position.x) * 180 / 3.141;

			sprite.setRotation(angle);
		}
	}
}