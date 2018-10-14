#include "pch.h"
#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

using namespace WorldConstants;

Zombie::Zombie()
{	
}

Zombie::~Zombie()
{
}

float Zombie::getMaxHealth() {
	return max_health;
}

float Zombie::getMaxSpeed() {
	return max_speed;
}

void Zombie::spawn(float startX, float startY, ZombieType type, int seed) {
	this->type = type;
	switch (type)
	{
	case ZombieType::BLOATER:
		max_speed = m_speed = 40;
		max_health = m_health = 5;

		m_sprite = Sprite(TextureHolder::getTexture("graphics/bloater.png"));
		break;
	case ZombieType::CHASER:
		max_speed = m_speed = 80;
		max_health = m_speed = 1;

		m_sprite = Sprite(TextureHolder::getTexture("graphics/chaser.png"));
		break;
	case ZombieType::CRAWLER:		
		max_speed = m_speed = 20;
		max_health = m_speed = 3;

		m_sprite = Sprite(TextureHolder::getTexture("graphics/crawler.png"));
		break;
	default:
		break;
	}

	// somewhere between 80 and 100
	float modifier = (rand() % MAX_VARIANCE) + OFFSET;

	// modify the speed to make the zombie unique
	srand((int)time(0) * seed);

	// express this as a fraction of 1
	modifier /= 100;
	// now equals between .7 and 1
	m_speed *= modifier;

	// initialize its location
	m_position.x = startX;
	m_position.y = startY;

	// set its origin to its center
	m_sprite.setOrigin(25, 25);
	// set its position
	m_sprite.setPosition(m_position);
}

bool Zombie::hit() {
	m_health--;

	if (m_health < 0) {
		// dead
		m_alive = false;
		m_sprite.setTexture(TextureHolder::getTexture("graphics/blood.png"));

		return true;
	}

	// injuried but not dead yet
	return false;
}

bool Zombie::isAlive() {
	return m_alive;
}

FloatRect Zombie::getPosition() {
	return m_sprite.getGlobalBounds();
}

Sprite Zombie::getSprite() {
	return m_sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// update the zombie position variables
	if (playerX > m_position.x) {
		m_position.x = m_position.x + m_speed * elapsedTime;
	}

	if (playerY > m_position.y) {
		m_position.y = m_position.y + m_speed * elapsedTime;
	}

	// move the sprite
	m_sprite.setPosition(m_position);

	// face the sprite in the correct direction
	float angle = (atan2(playerY - m_position.y, playerX - m_position.x) * 180) / WorldConstants::PI;
	m_sprite.rotate(angle);
}
