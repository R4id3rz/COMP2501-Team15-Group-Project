#pragma once
#include "SFML/Graphics.hpp"

class Config
{
public:
	//Player
	enum							inVehicle			{ VEH_TRUE = -1, VEH_FALSE = 1 };
	const static int				PLAYER_START_POS_X  = 400;
	const static int				PLAYER_START_POS_Y  = 450;
	static constexpr const char*	PLAYER_IMAGE		= "FriendlySlime.png"; //dont ask...
	

	//Zed
	static constexpr const char*	ZED_IMAGE			= "EnemySlime.png"; //...
	const static int				ZED_FOLLOW_DISTANCE	= 500;
	const static int				ZED_AMOUNT			= 4;

	//Window
	const static int				WINDOW_HEIGHT		= 900;
	const static int				WINDOW_WIDTH		= 1600;
	const static int				FPS					= 60;
};