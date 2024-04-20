#include "Racket.h"

#define RACKETSPEED 200

Racket::Racket()
{
}

Racket::Racket(sf::Vector2f startPoint, sf::Texture& texture, float topBorder, float bottomBorder)
{
	m_startPos = startPoint;
	m_sprite.setTexture(texture);
	auto texSýze = texture.getSize();
	sf::Vector2f playerOrigin = sf::Vector2f(texSýze.x / 2.0f, texSýze.y / 2.0f);
	m_sprite.setOrigin(playerOrigin);
	m_halfWidth = playerOrigin.x;
	m_halfHeight = playerOrigin.y;
	m_height = texSýze.y;
	m_topBorder = topBorder + (m_height / 2);
	m_bottomBorder = bottomBorder - (m_height / 2);
	reset();
}

void Racket::setPosition()
{
	m_sprite.setPosition(m_position);
}

void Racket::reset()
{
	m_position = m_startPos;
	setPosition();
}

void Racket::update(sf::Time t)
{
	m_position.y -= RACKETSPEED * m_moveDir * t.asSeconds();
	m_position.y = std::max(m_position.y, m_topBorder);
	m_position.y = std::min(m_position.y, m_bottomBorder);
	
	setPosition();
}

void Racket::addMoveDirection(float md)
{
	m_moveDir += md;
}

void Racket::setMoveDirection(float md)
{
	m_moveDir = md;
}

sf::Vector2f Racket::getPositon() const
{
	return m_position;
}

const sf::Sprite& Racket::getSprite() const
{
	return m_sprite;
}

float Racket::getHalfWidth() const
{
	return m_halfWidth;
}

float Racket::getHalfHeight() const
{
	return m_halfHeight;
}

float Racket::getHeight() const
{
	return m_height;
}
