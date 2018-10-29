#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TextureHolder.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Pickup.h"

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
	Time gameTimeTotal;
	//  where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	//  where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	Player player;
	IntRect arena;	
	Texture textureBackground;
	VertexArray background;

	// prepare for a horde of zombies
	int numZombies;
	int numZombiesAlive;
	//Zombie *zombies = nullptr;
	std::shared_ptr<Zombie> zombies;

	TextureHolder holder;

	Bullet bullets[WorldConstants::NUMBER_BULLETS];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1.0f;
	// when was the fire button last pressed?
	Time lastPressed;

	//Sprite spriteCrosshair;
	//Texture textureCrosshair;
	
	Pickup healthPickup;
	Pickup ammoPickup;

	// about the game
	int score = 0;
	int hiScore = 0;

	void handleInput();
	void update();
	void draw();
public:
	World();
	~World();
};

