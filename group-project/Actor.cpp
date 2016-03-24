#include "Actor.hpp"

Actor::Actor()
{

}

Actor::~Actor()
{}

void Actor::kill() {
	dead = true;
	sprite.setColor(sf::Color(200, 0, 0));
}