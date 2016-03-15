#pragma once
#include "SFML/Graphics.hpp"

#include "Config.hpp"
#include "Updateable.hpp"
#include "Renderable.hpp"

class Entity: public Renderable
{

public:
	Entity();
	~Entity();

	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::Image image;
	sf::Texture texture;
};