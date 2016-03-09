#include "Key.hpp"

Key::Key() {

}

Vehicle* Key::getVehicle() {
	return vehicle;
}

void Key::setVehicle(Vehicle* v) {
	vehicle = v;
}