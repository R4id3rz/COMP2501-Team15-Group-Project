#pragma once

#include "Actor.hpp"
#include "Fuel.hpp"

class Vehicle: public Actor {
public:
	Vehicle(float, float, float, int);				//Initialize consts and fuel, sets other variables to 0 or false
	~Vehicle();

	int getDirection();
	void setDirection(int);
	sf::Vector2f getVelocity();
	//void setVelocity(float, float);
	int getFuel();
	void addFuel(int);
	void decreaseFuel(int);

	void accelerate();								//Tell vehicle to be accelerating
	void reverse();									//Tell vehicle to decelerate
	void turnLeft();								//Tell vehicle to turn left
	void turnRight();								//Tell vehicle to turn right

	void update(sf::Time);
	float speed;									//Like velocity except without direction
protected:
	Fuel* fuel;
	int direction, delTurn;						//Direction in degreees, 0 = East-ward
	
	sf::Vector2f velocity;

	const float turnRate, acceleration, maxSpeed;
	bool accel, decel;
};