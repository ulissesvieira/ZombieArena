#include "pch.h"
#include "Player.h"

using namespace WorldConstants;

Player::Player() {
	resetHealth();	
	m_direction = Direction::STAND_BY;

	// associate a texture with the sprite
	m_texture.loadFromFile("graphics/player.png");
	m_sprite.setTexture(m_texture);
	// set the origin of the sprite to the centre
	// for smooth rotation
	m_sprite.setOrigin(25, 25);
}


Player::~Player() {
}

void Player::resetHealth() {
	m_speed = PLAYER_START_SPEED;
	m_health = PLAYER_START_HEALTH;
	m_maxHealth = PLAYER_START_HEALTH;
}

void Player::spawn(IntRect arena, Vector2i resolution, int tileSeize) {
	// place the player in the middle of the arena
	m_position.x = arena.width / 2;
	m_position.y = arena.height / 2;

	// copy the details of the arena to the player's m_arena
	m_arena.left = arena.left;
	m_arena.width = arena.width;
	m_arena.top = arena.top;
	m_arena.height = arena.height;

	// remember how big the tiles are in this arena
	m_tileSize = tileSeize;

	// store the resolution fir future use
	m_resolution.x = resolution.x;
	m_resolution.y = resolution.y;
}

void Player::resetPlayerStats() {
	resetHealth();

	m_direction = Direction::STAND_BY;
}

Time Player::getLastHitTime() {
	return m_lastHit;
}

bool Player::hit(Time timeHit) {
	if (timeHit.asMilliseconds() - m_lastHit.asMilliseconds() > 200) {
		m_lastHit = timeHit;
		m_health -= WorldConstants::HIT_DAMAGE;
		
		return true;
	}
	else {
		return false;
	}
}

FloatRect Player::getPosition() {
	return m_sprite.getGlobalBounds();
}

Vector2i Player::getCenter() {
	return m_position;
}

float Player::getRotation() {
	return m_sprite.getRotation();
}

Sprite Player::getSprite() {
	return m_sprite;
}

int Player::getHealth() {
	return m_health;
}

void Player::moveDirection(Direction direction) {
	m_direction = direction;
}

void Player::update(float elapsedTime, Vector2i mousePosition) {
	switch (m_direction) {
		case Direction::UP:
			m_position.y -= m_speed * elapsedTime;
			break;
		case Direction::DOWN:
			m_position.y += m_speed * elapsedTime;
			break;
		case Direction::LEFT:
			m_position.x -= m_speed * elapsedTime;
			break;
		case Direction::RIGHT:
			m_position.x += m_speed * elapsedTime;
			break;
		default:
			break;
	}

	m_sprite.setPosition(m_position.x, m_position.y);

	// keep the player in the arena
	if (m_position.x > m_arena.width - m_tileSize) {
		m_position.x = m_arena.width - m_tileSize;
	}

	if (m_position.x < m_arena.left + m_tileSize) {
		m_position.x = m_arena.left + m_tileSize;
	}

	if (m_position.y > m_arena.height - m_tileSize) {
		m_position.y = m_arena.height - m_tileSize;
	}

	if (m_position.y < m_arena.top + m_tileSize) {
		m_position.y = m_arena.top + m_tileSize;
	}

	// calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - m_resolution.y / 2, mousePosition.x - m_resolution.x / 2) * 180) / WORLD_PI;
	m_sprite.setRotation(angle);
}

void Player::upgradeSpeed() {
	// 20% speed upgrade
	m_speed += (PLAYER_START_SPEED * UPGRADE_PERCENT);
}

void Player::updradeHealth() {
	// 20% speed upgrade
	m_maxHealth += (PLAYER_START_HEALTH * UPGRADE_PERCENT);
}

void Player::increaseHealthLevel(int amount) {
	m_health += amount;

	// but not beyond the maximum
	if (m_health > m_maxHealth) {
		m_health = m_maxHealth;
	}
}