#pragma once

#include "Vehicle.hpp"
#include "Item.hpp"
#include "Entity.hpp"

class Key : public Item {
public:
	Key(int, int, Vehicle* = 0);
	Vehicle* getVehicle();
	void setVehicle(Vehicle*);
private:
	Vehicle* vehicle;
};