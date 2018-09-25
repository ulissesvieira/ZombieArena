#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;
using namespace WorldConstants;

class World
{
private:
	State state;
	Vector2i resolution;
	RenderWindow window;
	View mainView;

	// Here is our clock for timing everything
	Clock clock;

	// how long has the PLAYING state been active
	Time getTimeTotal;
	//  where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	//  where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	Player player;
	IntRect arena;	

	void handleInput();
public:
	World();
	~World();
};

