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

	virtual void update(sf::Time) = 0;

	std::vector<sf::Texture> textures;
	bool isDead;
};