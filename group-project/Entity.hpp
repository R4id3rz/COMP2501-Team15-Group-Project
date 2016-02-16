#pragma once
#include "SFML/Graphics.hpp"
#include "Config.hpp"

class Entity
{

public:
	Entity();
	~Entity();

	sf::Vector2f position;
	sf::Vector2f velocity;
};