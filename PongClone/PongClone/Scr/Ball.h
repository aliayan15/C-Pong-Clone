#pragma once
#include"Vec2f.h"
#include"SFML/Graphics.hpp"
#include"iostream"


class Ball
{
public:
	Ball();
	Ball(sf::Vector2f startPoint, sf::Texture& texture);

	void update(sf::Time t);
	void reset();
	void bounceTopAndBottom();
	void bounceFromRacket(float racketY, float racketHalfHeight);

	const sf::Sprite& getSprite() const;
	sf::Vector2f getPositon() const;
	sf::Vector2f getTopPoint() const;
	sf::Vector2f getBottomPoint() const;
	sf::Vector2f getRightPoint() const;
	sf::Vector2f getLeftPoint() const;
	float getHalfWidth() const;

private:
	void setPosition();

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_startPos;
	myUtility::Vec2f m_velocity;
	float m_halfWidth = 0;
	float m_ballStartSpeed = 400;
	float m_ballSpeed;

};

