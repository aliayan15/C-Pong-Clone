#include "PvPmodeScene.h"
#include"Vec2f.h"

#define PLAYERSPACE 10
#define UPPERSPACE 47
#define RACKETSPEED 5
#define RACKETHALFHEIGHT 60


using namespace myUtility;

PvPmodeScene::PvPmodeScene(GameEngine* game) :SceneBase(game)
{
	init();
}

void PvPmodeScene::init()
{
	m_isPlaying = false;
	std::srand(std::time(0));
	m_windowSize = m_game->getWindow().getSize();
	m_tekoFont = m_game->getAssets().getFont("teko");
	auto& arialFont = m_game->getAssets().getFont("arial");
	// board
	m_sBoard.setTexture(m_game->getAssets().getTexture("board"));
	m_sBoard.setPosition(0, UPPERSPACE);
	// score
	auto& leftScoreText = m_game->getAssets().getTexture("bar");
	m_sLeftScore.setTexture(leftScoreText);
	m_sRightScore.setTexture(leftScoreText);
	m_sRightScore.setScale(-1, 1);
	m_sRightScore.setPosition(m_windowSize.x, 0);

	const float textPosX = (float)m_windowSize.x / 2;
	InitText(m_tLeftScore, std::to_string(m_leftPlayerScore), 42, sf::Color::Black, true, sf::Vector2f(textPosX - 150, -5), m_tekoFont);
	InitText(m_tRightScore, std::to_string(m_rightPlayerScore), 42, sf::Color::Black, true, sf::Vector2f(textPosX + 150, -5), m_tekoFont);
	InitText(m_tLeftPlayer, "Player 1", 24, sf::Color::Black, false, sf::Vector2f(textPosX - 300, 5), arialFont);
	InitText(m_tRightPlayer, "Player 2", 24, sf::Color::Black, false, sf::Vector2f(textPosX + 300, 5), arialFont);

	// rackets
	auto& t_leftRacket = m_game->getAssets().getTexture("left");
	m_leftRacket = Racket(sf::Vector2f(PLAYERSPACE, m_windowSize.y / 2.0f), t_leftRacket, UPPERSPACE, m_windowSize.y);
	auto& t_rightRacket = m_game->getAssets().getTexture("right");
	m_rightRacket = Racket(sf::Vector2f(m_windowSize.x - PLAYERSPACE, m_windowSize.y / 2.0f), t_rightRacket, UPPERSPACE, m_windowSize.y);

	// ball
	auto& tex_ball = m_game->getAssets().getTexture("ball");
	m_ball = Ball(sf::Vector2f(m_windowSize.x / 2.0f, m_windowSize.y / 2.0f), tex_ball);

	// start text
	InitText(m_tStartText, "Press SPACE to Start", 32, sf::Color::White, false,
		sf::Vector2f(m_ball.getPositon().x, m_ball.getPositon().y + 40), m_tekoFont);

	registerPlayerInputs();
	// render
	m_game->getWindow().clear();
	render();
	m_game->getWindow().draw(m_tStartText);
	m_game->getWindow().display();
}

void PvPmodeScene::registerPlayerInputs()
{
	// actions
	registerAction(sf::Keyboard::Space, ActionName::SPACE);
	registerAction(sf::Keyboard::Up, ActionName::UP);
	registerAction(sf::Keyboard::Down, ActionName::DOWN);
	registerAction(sf::Keyboard::W, ActionName::W);
	registerAction(sf::Keyboard::S, ActionName::S);
	registerAction(sf::Keyboard::Enter, ActionName::ENTER);
}

void PvPmodeScene::update()
{
	sf::Time elapsed = m_clock.restart();
	if (!m_isPlaying) return;

	// players  movement
	m_rightRacket.update(elapsed);
	m_leftRacket.update(elapsed);

	// ball movement and racket collision
	m_ball.update(elapsed);

	auto& ballPos = m_ball.getPositon();
	BallRacketCollisionCheck(ballPos);

	// out of board and score
	if (m_ball.getLeftPoint().x < 0)
	{
		m_rightPlayerScore++;
		UpdateScore();
		reStart();
		return;
	}
	if (m_ball.getRightPoint().x > m_windowSize.x)
	{
		m_leftPlayerScore++;
		UpdateScore();
		reStart();
		return;
	}

	// ball board bounce
	if (m_ball.getBottomPoint().y > m_windowSize.y || m_ball.getTopPoint().y < UPPERSPACE)
	{
		m_ball.bounceTopAndBottom();
	}

	m_game->getWindow().clear();
	render();
	m_game->getWindow().display();
}

void PvPmodeScene::BallRacketCollisionCheck(const sf::Vector2f& ballPos)
{
	if (isBoxesIntersect(m_rightRacket))
	{
		if (ballPos.x > m_rightRacket.getPositon().x - m_rightRacket.getHalfWidth() + 2) return;

		m_ball.bounceFromRacket(m_rightRacket.getPositon().y, RACKETHALFHEIGHT);
		return;
	}
	if (isBoxesIntersect(m_leftRacket))
	{
		if (ballPos.x < m_leftRacket.getPositon().x + m_leftRacket.getHalfWidth() - 2) return;

		m_ball.bounceFromRacket(m_leftRacket.getPositon().y, RACKETHALFHEIGHT);
		return;
	}
}

bool PvPmodeScene::isBoxesIntersect(Racket& b)
{
	auto& bPos = b.getPositon();
	return (abs(m_ball.getPositon().x - bPos.x) < (m_ball.getHalfWidth() + b.getHalfWidth())) &&
		(abs(m_ball.getPositon().y - bPos.y) * 2 <= b.getHeight() + 4);
}

void PvPmodeScene::reStart()
{
	m_ball.reset();
}

void PvPmodeScene::render()
{
	m_game->getWindow().draw(m_sBoard);
	m_game->getWindow().draw(m_sLeftScore);
	m_game->getWindow().draw(m_sRightScore);
	m_game->getWindow().draw(m_tLeftScore);
	m_game->getWindow().draw(m_tRightScore);
	m_game->getWindow().draw(m_tLeftPlayer);
	m_game->getWindow().draw(m_tRightPlayer);
	m_game->getWindow().draw(m_rightRacket.getSprite());
	m_game->getWindow().draw(m_leftRacket.getSprite());
	m_game->getWindow().draw(m_ball.getSprite());
}

void PvPmodeScene::doAction(const Action& action)
{
	if (action.type() == ActionType::Pressed)
	{
		if (action.name() == ActionName::SPACE && !m_isPlaying)
		{
			m_isPlaying = true;
			removeAction(sf::Keyboard::Space);
		}
		if (action.name() == ActionName::ENTER && !m_isPlaying)
		{
			m_game->changeScene(SceneName::Menu);
		}

		if (action.name() == ActionName::UP)
			m_rightRacket.addMoveDirection(1);
		if (action.name() == ActionName::DOWN)
			m_rightRacket.addMoveDirection(-1);

		if (action.name() == ActionName::W)
			m_leftRacket.addMoveDirection(1);
		if (action.name() == ActionName::S)
			m_leftRacket.addMoveDirection(-1);
	}
	else
	{
		if (action.name() == ActionName::UP)
			m_rightRacket.addMoveDirection(-1);
		if (action.name() == ActionName::DOWN)
			m_rightRacket.addMoveDirection(1);
		if (action.name() == ActionName::W)
			m_leftRacket.addMoveDirection(-1);
		if (action.name() == ActionName::S)
			m_leftRacket.addMoveDirection(1);
	}
}

void PvPmodeScene::UpdateScore()
{
	m_tLeftScore.setString(std::to_string(m_leftPlayerScore));
	m_tRightScore.setString(std::to_string(m_rightPlayerScore));
	bool isGameEnd = m_leftPlayerScore >= GAMEENDSCORE || m_rightPlayerScore >= GAMEENDSCORE;
	if (isGameEnd)
	{
		m_isPlaying = false;
		std::string winText = m_leftPlayerScore >= GAMEENDSCORE ? "Player 1 WON" : "Player 2 WON";
		sf::Text t_PlayerWon;
		sf::Text t_getBackMenu;;
		InitText(t_PlayerWon, winText, 56, sf::Color::White, true, sf::Vector2f(m_windowSize.x / 2.0f, m_windowSize.y / 2.0f - 30), m_tekoFont);
		InitText(t_getBackMenu, "Press enter to go back to menu", 24,
			sf::Color::White, false, sf::Vector2f(m_windowSize.x / 2.0f, m_windowSize.y / 2.0f + 50), m_tekoFont);
		m_game->getWindow().clear();
		render();
		m_game->getWindow().draw(t_PlayerWon);
		m_game->getWindow().draw(t_getBackMenu);
		m_game->getWindow().display();
	}
}


