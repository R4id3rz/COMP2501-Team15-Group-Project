#pragma once

#include "Item.hpp"
#include "Entity.hpp"

class Fuel : public Item {
public:
	Fuel(int, int, int);
	sf::Vector2f getPosition();
	int getAmount();
	void setAmount(int);
	void addFuel(int);
	void removeFuel(int);
private:
	int fuelAmount;
};