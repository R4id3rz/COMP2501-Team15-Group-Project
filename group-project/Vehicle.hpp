#pragma once

#include "Actor.hpp"

class Vehicle: public Actor {
public:
	Vehicle(float, float, float, int);				//Initialize consts and fuel, sets other variables to 0 or false
	virtual ~Vehicle() = 0;

	float getDirection();

	void accelerate();								//Tell vehicle to be accelerating
	void reverse();									//Tell vehicle to decelerate
	void turnLeft();								//Tell vehicle to turn left
	void turnRight();								//Tell vehicle to turn right

	void update();
private:
	int fuel;
	float direction, delTurn;						//Direction in degreees, 0 = East-ward
	float speed;									//Like velocity except without direction


	const float turnRate, acceleration, maxSpeed;
	bool accel, decel;
};