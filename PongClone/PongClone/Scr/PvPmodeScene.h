#pragma once
#include "GameEngine.h"
#include"Vec2f.h"
#include"Ball.h"
#include"Racket.h"

#define GAMEENDSCORE 10

class PvPmodeScene :public SceneBase
{
public:
	PvPmodeScene(GameEngine* game);

protected:
	// Inherited via SceneBase
	void update() override;
	void doAction(const Action& action) override;

	void init();
	virtual void registerPlayerInputs();
	virtual void render();
	virtual void updateScore();
	sf::Vector2f getIntersect(const Racket& b);
	void ballRacketCollisionCheck();
	void reStart();

protected:
	sf::Vector2u m_windowSize;
	sf::Font m_tekoFont;
	sf::Sprite m_sBoard;
	sf::Sprite m_sRightScore;
	sf::Sprite m_sLeftScore;
	sf::Text m_tRightScore;
	sf::Text m_tLeftScore;
	sf::Text m_tRightPlayer;
	sf::Text m_tLeftPlayer;
	sf::Text m_tStartText;
	int m_leftPlayerScore = 0;
	int m_rightPlayerScore = 0;
	bool m_isPlaying = false;

	Ball m_ball;
	Racket m_leftRacket;
	Racket m_rightRacket;
	sf::Clock m_clock;
};
