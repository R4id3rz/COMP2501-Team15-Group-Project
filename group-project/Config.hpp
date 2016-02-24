#pragma once
#include "SFML/Graphics.hpp"

#define PI 3.141592

//Vehicle consts
//Tank
#define TANKMAXSPEED		2
#define TANKTURNRATE		1
#define TANKACCELERATION	0.05
#define TANKFUEL			15000
//Car
#define CARMAXSPEED			10
#define CARTURNRATE			4
#define CARACCELERATION		0.1
#define CARFUEL				6000
//Truck
#define	TRUCKMAXSPEED		4
#define	TRUCKTURNRATE		2
#define	TRUCKACCELERATION	0.6
#define	TRUCKFUEL			10000

#define TILESIZE			64

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

	//iunno
};