#pragma once

#include "Vehicle.hpp"

class Tank: public Vehicle {
public:
	Tank(float, float);
	~Tank();

	void update(sf::Time);

private:
};