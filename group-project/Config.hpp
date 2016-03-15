#pragma once
#include "SFML/Graphics.hpp"

#define PI 3.141592

//Vehicle consts
//Tank
#define TANKMAXSPEED		0.1
#define TANKTURNRATE		1
#define TANKACCELERATION	0.001
#define TANKFUEL			25000
//Car
#define CARMAXSPEED			0.5
#define CARTURNRATE			4
#define CARACCELERATION		0.01
#define CARFUEL				10000
//Truck
#define	TRUCKMAXSPEED		2
#define	TRUCKTURNRATE		2
#define	TRUCKACCELERATION	0.1
#define	TRUCKFUEL			15000

#define TILESIZE			64

enum TILETYPE { Tree = 0, Grass = 1, vRoad = 2, hRoad = 3, neRoad = 4, esRoad = 5, swRoad = 6, wnRoad = 7,
				zGrass = 8, zvRoad = 9, zhRoad = 10, zneRoad = 11, zesRoad = 12, zswRoad = 13, zwnRoad = 14,
				Start = 15, End = 16};
static sf::Vector2f tileCoords[17];

class Config
{
public:
	//Window
	const static int				WINDOW_WIDTH = 1024;
	const static int				WINDOW_HEIGHT = 640;
	const static int				FPS = 60;

	//Player
	enum							inVehicle			{ VEH_TRUE = -1, VEH_FALSE = 1 };	//used to change Zed movements to negative, AKA running away
	const static int				PLAYER_START_POS_X  = 400;
	const static int				PLAYER_START_POS_Y  = 450;
	static constexpr const char*	PLAYER_IMAGE		= "Assets/FriendlySlime.png";				//constexpr is used to bypass some fked up C++ syntax bullshit
	static constexpr const double	PLAYER_VELOCITY		= 0.2;
	const static int				VEH_ENTER_DISTANCE	= 20;

	//Zed
	static constexpr const char*	ZED_IMAGE			= "Assets/EnemySlime.png";
	const static int				ZED_FOLLOW_DISTANCE	= 300;								//Zeds will follow under this distance
	const static int				ZED_AMOUNT			= 4;
	const static int				ZED_KILL_DISTANCE	= 10;
	static constexpr const double	ZED_VELOCITY		= 0.1;

	//Tank
	static constexpr const char*	TANK_IMAGE			= "Assets/Tank.png";
	const static int				IDLE_USAGE			= 5;
	const static int				MOVING_USAGE		= 15;

	//Car
	static constexpr const char*	CAR_IMAGE			= "Assets/Car.png";

	//Fuel
	const static int				DEFAULT_FUEL		= 10000;
	static constexpr const char*	FUEL_IMAGE			= "Assets/JerryCan.png";
};