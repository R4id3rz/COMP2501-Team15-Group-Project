#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"


class Actor : public Entity, public Updateable
{

public:
	Actor();
	~Actor();

	bool dead;
	void kill();
};