#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
private:
	// the sprite that represents this pickup
	Sprite m_sprite;

	// the arena it exists in
	IntRect m_arena;

	// how much is this pick worth?
	int m_value;

	// what type of pickup is this?
	WorldConstants::PickupType m_type;

	bool m_spawned;
	float m_secondsSinceSpawn = 0;
	float m_secondsSinceDeSpawn = 0;
	float m_secondsToLive;
	float m_secondsToWait;

	void initPickup(WorldConstants::PickupType type);
public:
	Pickup();	
	~Pickup();

	Pickup(WorldConstants::PickupType type);

	void setType(WorldConstants::PickupType type);

	// prepare a new pickup
	void setArena(IntRect arena);
	void spawn();

	// check the position of a pickup
	FloatRect getPosition();
	// get the sprite for drawing
	Sprite getSprite();
	// let the pickup update itself each frame
	void update(float elapsedTime);
	// is this pickup currently spawned?
	bool isSpawned();
	// get the goodness form the pickup
	int gotIt();
	// upgrade the value of each pickup
	void upgrade();
};

