#include "pch.h"
#include "Pickup.h"
#include "TextureHolder.h"

using namespace WorldConstants;

#define ARENA_OFFSET 50;

Pickup::Pickup()
{
}


Pickup::~Pickup()
{
}

template<typename Enumeration>
auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

Pickup::Pickup(PickupType type)
{
	m_type = type;
	initPickup(type);
}

void Pickup::setType(PickupType type) {
	initPickup(type);
}

void Pickup::initPickup(PickupType type) {
	m_type = type; 
	if (type == PickupType::HEALTH) {
		m_sprite = Sprite(TextureHolder::getTexture("graphics/health_pickup.png"));
		m_value = HEALTH_START_VALUE;
	}
	else {
		m_sprite = Sprite(TextureHolder::getTexture("graphics/ammo_pickup.png"));
		m_value = AMMO_START_VALUE;
	}

	m_sprite.setOrigin(25, 25);
	m_secondsToLive = START_SECONDS_TO_LIVE;
	m_secondsToWait = START_WAIT_TIME;
}

void Pickup::setArena(IntRect arena) {
	m_arena.left = arena.left + ARENA_OFFSET;
	m_arena.width = arena.width - ARENA_OFFSET;
	m_arena.top = arena.top + ARENA_OFFSET;
	m_arena.height = arena.height - ARENA_OFFSET;

	spawn();
}

void Pickup::spawn() {
	// spawn at a random location
	srand((int)time(0) / as_integer(m_type));
	int x = (rand() % m_arena.width);

	srand((int)time(0) / as_integer(m_type));
	int y = (rand() % m_arena.height);

	m_secondsSinceSpawn = 0;
	m_spawned = true;
	m_sprite.setPosition(x, y);
}

FloatRect Pickup::getPosition() {
	return m_sprite.getGlobalBounds();
}

Sprite Pickup::getSprite() {
	return m_sprite;
}

bool Pickup::isSpawned() {
	return m_spawned;
}

int Pickup::gotIt() {
	m_spawned = false;
	m_secondsSinceDeSpawn = 0;

	return as_integer(m_type);
}

void Pickup::update(float elapsedTime) {
	if (m_spawned) {
		m_secondsSinceSpawn += elapsedTime;
	} 
	else {
		m_secondsSinceDeSpawn += elapsedTime;
	}

	// Do we need to hide a pickup?
	if (m_secondsSinceSpawn > m_secondsToLive && m_spawned)
	{
		// Revove the pickup and put it somewhere else
		m_spawned = false;
		m_secondsSinceDeSpawn = 0;
	}

	// Do we need to spawn a pickup
	if (m_secondsSinceDeSpawn > m_secondsToWait && !m_spawned)
	{
		// spawn the pickup and reset the timer
		spawn();
	}
}

void Pickup::upgrade() {
	if (m_type == PickupType::HEALTH) {
		m_value += (HEALTH_START_VALUE * .5);
	}
	else {
		m_value += (AMMO_START_VALUE * .5);
	}

	// Make them more frequent and last longer
	m_secondsToLive += (START_SECONDS_TO_LIVE / 10);
	m_secondsToWait -= (START_WAIT_TIME / 10);
}