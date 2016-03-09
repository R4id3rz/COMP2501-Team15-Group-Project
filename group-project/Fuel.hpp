#pragma once

#include "Item.hpp"
#include "Entity.hpp"

class Fuel : public Item {
public:
	Fuel();
	int getAmount();
	void setAmount(int);
private:
	int fuelAmount;
};