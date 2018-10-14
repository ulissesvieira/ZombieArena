#pragma once
#include <SFML/Graphics.hpp>
#include "WorldConstants.h"

using namespace sf;

class Zombie
{
private:
	const int MAX_VARIANCE = 30;
	const int OFFSET = 101 - MAX_VARIANCE;

	WorldConstants::ZombieType type;
	float max_speed;
	float max_health;

	// where the zombie is
	Vector2f m_position;
	Sprite m_sprite;
	// how fast can this one run/craw?
	float m_speed;
	// how much health has it got?
	float m_health;

	// is it still alive?
	bool m_alive;
public:
	Zombie();
	~Zombie();

	float getMaxHealth();
	float getMaxSpeed();

	// handle when a bullet hits a zombie
	bool hit();

	bool isAlive();

	// spawn a new zombie
	void spawn(float startX, float startY, WorldConstants::ZombieType type, int seed);
	Sprite getSprite();

	// return a rectangle that is the position in the world
	FloatRect getPosition();

	// update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation);
};

