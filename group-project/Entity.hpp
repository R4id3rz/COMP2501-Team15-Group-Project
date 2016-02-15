#pragma once
#include "SFML/Graphics.hpp"

class Entity
{

public:
	Entity();
	~Entity();

	sf::Vector2f position;
	sf::Vector2f velocity;
};