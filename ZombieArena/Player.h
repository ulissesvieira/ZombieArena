#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	// where is the player
	Vector2f m_position;

	Sprite m_sprite;
	Texture m_texture;

	// What is the screen resolution
	Vector2f m_resolution;
	// What size is the current arena
	IntRect m_arena;
	// How big is each tile of the arena
	int m_tileSize;

	// Which directions is the player currently moving in
	WorldConstants::Direction m_direction;
	/* bool m_upPressed;
	bool m_downPressed;
	bool m_leftPressed;
	bool m_rightPressed;*/

	// how much health has the player got?
	int m_health;
	// What is the maximum health the player can have
	int m_maxHealth;
	// when was the player last hit time
	Time m_lastHit;
	// speed in pixels per second
	float m_speed;

	void resetHealth();
public:
	Player();
	~Player();

	void spawn(IntRect, Vector2f, int);

	// call this at the end of every game
	void resetPlayerStats();
	// handle the player getting hit by a zombie
	bool hit(Time timeHit);

	// how long ago was the player last hit
	Time getLastHitTime();
	// where is the player
	FloatRect getPosition();
	// where is the center of the player 
	Vector2f getCenter();
	// which angle is the player facing
	float getRotation();
	// send a copy of the sprite to main
	Sprite getSprite();

	void moveDirection(WorldConstants::Direction);
	/*void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// stop the player moving in a specific direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();*/

	// we will call theis function once every frame
	void update(float, Vector2i);
	// give the player a speed boost
	void upgradeSpeed();

	// git the player some health
	void updradeHealth();
	// how much health has the player currently got?
	int getHealth();
	// how much the health of the player will be increase
	void increaseHealthLevel(int);
};

