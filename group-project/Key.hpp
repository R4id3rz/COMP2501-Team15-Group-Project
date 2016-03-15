#pragma once

#include "Vehicle.hpp"
#include "Item.hpp"
#include "Entity.hpp"

class Key : public Item {
public:
	Key();
	Vehicle* getVehicle();
	void setVehicle(Vehicle*);
private:
	Vehicle* vehicle;
};