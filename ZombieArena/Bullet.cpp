#include "pch.h"
#include "Bullet.h"

Bullet::Bullet()
{
	m_shape.setSize(sf::Vector2f(2,2));
}

Bullet::~Bullet()
{
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY) {
	// calculate the gradient of the flight path
	float gradient = (startX - targetX) / (startY - targetY);

	// keep track of the bullet
	m_inFlight = true;
	m_position.x = startX;
	m_position.y = startY;

	// any gradient less than 1 needs to be negative
	if (gradient < 1) {
		gradient *= -1;
	}

	// calculate the ratio between x and y
	float ratioXY = m_speed / (1 + gradient);

	// set the speed horizontally and vertically
	m_distanceY = ratioXY;
	m_distanceX = ratioXY * gradient;

	// point the bullet in the right direction
	if (targetX < startX) {
		m_distanceX *= -1;
	}

	if (targetY < startY) {
		m_distanceY *= -1;
	}

	m_minX = startX - WorldConstants::BULLET_MAX_RANGE;
	m_maxX = startX + WorldConstants::BULLET_MAX_RANGE;
	m_minY = startY - WorldConstants::BULLET_MAX_RANGE;
	m_maxY = startY + WorldConstants::BULLET_MAX_RANGE;

	// position the bullet ready to be drawn
	m_shape.setPosition(m_position);
}

void Bullet::stop() {
	m_inFlight = false;
}

bool Bullet::isInFlight() {
	return m_inFlight;
}

FloatRect Bullet::getPosition(){
	return m_shape.getGlobalBounds();
}

RectangleShape Bullet::getShape() {
	return m_shape;
}

void Bullet::update(float elapsedTime) {
	// update the bullet position variables
	m_position.x += m_distanceX * elapsedTime;
	m_position.y += m_distanceY * elapsedTime;

	// move the bullet
	m_shape.setPosition(m_position);

	// has the bullet gone out of range?
	if (m_position.x < m_minX || m_position.x > m_maxX || m_position.y < m_minY || m_position.y > m_maxY) {
		m_inFlight = false;
	}
}