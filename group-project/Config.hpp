#pragma once
#include "SFML/Graphics.hpp"

class Config
{
public:
	//Window
	const static int				WINDOW_WIDTH = 1600;
	const static int				WINDOW_HEIGHT = 900;
	const static int				FPS = 60;

	//Player
	enum							inVehicle			{ VEH_TRUE = -1, VEH_FALSE = 1 };	//used to change Zed movements to negative, AKA running away
	const static int				PLAYER_START_POS_X  = 400;
	const static int				PLAYER_START_POS_Y  = 450;
	static constexpr const char*	PLAYER_IMAGE		= "FriendlySlime.png";				//constexpr is used to bypass some fked up C++ syntax bullshit
	static constexpr const double	PLAYER_VELOCITY		= 0.2;

	//Zed
	static constexpr const char*	ZED_IMAGE			= "EnemySlime.png";
	const static int				ZED_FOLLOW_DISTANCE	= 500;								//Zeds will follow under this distance
	const static int				ZED_AMOUNT			= 4;
	const static int				ZED_KILL_DISTANCE	= 10;
	static constexpr const double	ZED_VELOCITY		= 0.1;
};