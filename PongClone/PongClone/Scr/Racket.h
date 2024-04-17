#pragma once
#include"SFML/Graphics.hpp"

class Racket
{
public:
	Racket();
	Racket(sf::Vector2f startPoint, sf::Texture& texture,float topBorder,float bottomBorder);
	
	void reset();
	void update(sf::Time t);
	void addMoveDirection(float md);
	void setMoveDirection(float md);

	const sf::Vector2f& getPositon();
	const sf::Sprite& getSprite();
	const float getHalfWidth();
	const float getHeight();
private:
	void setPosition();
private:
	float m_topBorder = 0;
	float m_bottomBorder = 0;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_startPos;
	float m_halfWidth = 0;
	float m_height = 0;
	float m_moveDir = 0;
};

