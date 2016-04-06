#pragma once

#include "Model.hpp"
#include "View.hpp"
#include "Config.hpp"

class Controller
{
public:
	Controller(Model*, View*);
	~Controller();

	Model* model;
	View* view;

	bool keyReleased;

	void inputs();
};