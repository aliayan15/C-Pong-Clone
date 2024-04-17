#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(sf::Vector2f startPoint, sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	auto size = texture.getSize();
	m_halfWidth = size.x / 2.0f;
	m_sprite.setOrigin(size.x / 2.0f, size.y / 2.0f);
	m_startPos = startPoint;

	reset();
}

void Ball::setPosition()
{
	m_sprite.setPosition(m_position);
}

void Ball::update(sf::Time t)
{
	m_position.x += m_velocity.x * t.asSeconds();
	m_position.y += m_velocity.y * t.asSeconds();
	setPosition();
}

void Ball::reset()
{
	m_position = m_startPos;
	setPosition();

	auto rnd_num = std::rand() % 100;
	myUtility::Vec2f ballDir;
	ballDir.x = rnd_num > 50 ? 1 : -1;
	ballDir.y = std::cosf(((std::rand() % 160) - 80) * 0.017f);
	ballDir = ballDir.normalized();
	m_ballSpeed = m_ballStartSpeed;
	m_velocity = ballDir * (m_ballSpeed - 150);
}

const sf::Vector2f& Ball::getPositon()
{
	return m_position;
}

const sf::Vector2f Ball::getTopPoint()
{
	return sf::Vector2f(m_position.x, m_position.y - m_halfWidth);
}

const sf::Vector2f Ball::getBottomPoint()
{
	return sf::Vector2f(m_position.x, m_position.y + m_halfWidth);
}

const sf::Vector2f Ball::getRightPoint()
{
	return sf::Vector2f(m_position.x + m_halfWidth, m_position.y);
}

const sf::Vector2f Ball::getLeftPoint()
{
	return sf::Vector2f(m_position.x - m_halfWidth, m_position.y);
}

const sf::Sprite& Ball::getSprite()
{
	return m_sprite;
}

const float Ball::getHalfWidth()
{
	return m_halfWidth;
}

void Ball::bounceTopAndBottom()
{
	m_velocity.y *= -1;
}

void Ball::bounceFromRacket(float racketY, float racketHalfHeight)
{
	m_ballSpeed += 10;
	float dir = (m_position.y - racketY) / racketHalfHeight;
	dir *= 1.2f;
	dir *= (m_ballSpeed / 2.0f);

	m_velocity.x *= -1;
	m_velocity.y = dir;
	m_velocity = m_velocity.normalized() * m_ballSpeed;
}