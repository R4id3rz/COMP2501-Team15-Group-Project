#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Updateable.hpp"
#include "Renderable.hpp"

class Actor : public Entity, public Updateable, public Renderable
{

public:
	Actor();
	~Actor();

	sf::Image image;
	std::vector<sf::Texture> textures;
	bool isDead;
};