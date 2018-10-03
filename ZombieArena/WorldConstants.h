#pragma once

#ifdef _DEBUG
#include <iostream>
#define D(x) x
#else
#define D(x)
#endif // DEBUG


namespace WorldConstants {
	const float PLAYER_START_SPEED = 200.0;
	const float PLAYER_START_HEALTH = 100.0;
	const int HIT_DAMAGE = 10;
	const float WORLD_PI = 3.141;
	const float UPGRADE_PERCENT = 0.2; // 20%

	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	enum class Direction {
		STAND_BY, LEFT, RIGHT, UP, DOWN
	};

	enum class State {
		PAUSED, LEVELING_UP, GAME_OVER, PLAYING
	};
}