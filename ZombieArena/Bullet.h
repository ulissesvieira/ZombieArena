#pragma once
#include <SFML/Graphics.hpp>
#include "WorldConstants.h"

using namespace sf;

class Bullet
{
private:
	// where is the bullet?
	Vector2f m_position;
	// what each bullet looks like
	RectangleShape m_shape;

	// is this bullet currently whizzing through the air
	bool m_inFlight = false;
	// how fast does a bullet travel:
	float m_speed = WorldConstants::BULLET_SPEED;

	// what fraction of 1 pixel does the bullet travel
	// horizontally and vertically each frame?
	// these values will be derived from m_speed
	float m_distanceX;
	float m_distanceY;

	// some boundaries so the bullet doesn't fly forever
	float m_maxX;
	float m_minX;
	float m_maxY;
	float m_minY;
public:
	Bullet();
	~Bullet();

	void stop();
	bool isInFlight();
	void update(float elapsedTime);

	// launch a new bullet
	void shoot(float startX, float startY, float xTarget, float yTarget);

	// tell the calling code where the bullet is in the world
	FloatRect getPosition();

	RectangleShape getShape();
};

