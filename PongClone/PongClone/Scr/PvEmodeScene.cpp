#include "PvEmodeScene.h"

PvEmodeScene::PvEmodeScene(GameEngine* game) :PvPmodeScene(game)
{
	init();
}

void PvEmodeScene::init()
{
	m_tRightPlayer.setString("AI Player");

	// render
	m_game->getWindow().clear();
	render();
	m_game->getWindow().draw(m_tStartText);
	m_game->getWindow().display();
}

void PvEmodeScene::update()
{
	int aiMoveDir = m_rightRacket.getPositon().y - m_ball.getPositon().y;
	if (std::abs(aiMoveDir) > 40)
	{
		aiMoveDir = std::min(aiMoveDir, 1);
		aiMoveDir = std::max(aiMoveDir, -1);
		m_rightRacket.setMoveDirection(aiMoveDir);
	}
	else if (std::abs(aiMoveDir) < 10)
	{
		m_rightRacket.setMoveDirection(0);
	}
	
	PvPmodeScene::update();
}

void PvEmodeScene::doAction(const Action& action)
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

		if (action.name() == ActionName::W)
			m_leftRacket.addMoveDirection(1);
		if (action.name() == ActionName::S)
			m_leftRacket.addMoveDirection(-1);
	}
	else
	{
		if (action.name() == ActionName::W)
			m_leftRacket.addMoveDirection(-1);
		if (action.name() == ActionName::S)
			m_leftRacket.addMoveDirection(1);
	}
}

void PvEmodeScene::registerPlayerInputs()
{
	registerAction(sf::Keyboard::Space, ActionName::SPACE);
	registerAction(sf::Keyboard::W, ActionName::W);
	registerAction(sf::Keyboard::S, ActionName::S);
	registerAction(sf::Keyboard::Enter, ActionName::ENTER);
}

void PvEmodeScene::render()
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

void PvEmodeScene::UpdateScore()
{
	m_tLeftScore.setString(std::to_string(m_leftPlayerScore));
	m_tRightScore.setString(std::to_string(m_rightPlayerScore));
	bool isGameEnd = m_leftPlayerScore >= GAMEENDSCORE || m_rightPlayerScore >= GAMEENDSCORE;
	if (isGameEnd)
	{
		m_isPlaying = false;
		std::string winText = m_leftPlayerScore >= GAMEENDSCORE ? "Player 1 WON" : "AI Player WON";
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


