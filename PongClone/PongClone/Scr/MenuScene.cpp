#include "MenuScene.h"

MenuScene::MenuScene(GameEngine* game) :SceneBase(game)
{
	init();
}

void MenuScene::init()
{
	m_windowSize = m_game->getWindow().getSize();
	m_tekoFont = m_game->getAssets().getFont("teko");
	float windowHalfWith = (float)m_windowSize.x / 2;
	// title
	InitText(m_tTitle, "PONG", 48, sf::Color(160, 32, 240), true, sf::Vector2f(windowHalfWith, 30), m_tekoFont);
	// made by text
	InitText(m_tMadeBy, "Made by Ali Ayan", 24, sf::Color(160, 32, 240), false,
		sf::Vector2f(windowHalfWith, 50 + m_tTitle.getGlobalBounds().height), m_tekoFont);
	// options
	InitOptions(m_sbtn1, m_tbtn1, 220, "2 Player");
	InitOptions(m_sbtn2, m_tbtn2, 280, "1 Player");
	InitText(m_tDescription, "Use arrow keys to select game mode and Press Enter.", 20, sf::Color::White, false,
		sf::Vector2f(windowHalfWith, 400), m_game->getAssets().getFont("arial"));

	m_selectedGameMode = 0;
	SelectGameMode();
	// actions
	registerAction(sf::Keyboard::Up, ActionName::UP);
	registerAction(sf::Keyboard::Down, ActionName::DOWN);
	registerAction(sf::Keyboard::Enter, ActionName::ENTER);
}

void MenuScene::InitOptions(sf::RectangleShape& s, sf::Text& t, float y, const char* text)
{
	s = sf::RectangleShape(sf::Vector2f(140.f, 40.f));
	s.setFillColor(sf::Color::White);
	s.setOrigin(70, 20);
	s.setPosition((float)m_windowSize.x / 2, y);

	t.setFont(m_game->getAssets().getFont("teko"));
	t.setString(text);
	t.setCharacterSize(26);
	t.setFillColor(sf::Color::Black);
	t.setStyle(sf::Text::Bold);
	auto b3 = t.getGlobalBounds();
	t.setOrigin(sf::Vector2f(b3.width / 2, b3.height / 2));
	t.setPosition((float)m_windowSize.x / 2, y - 5);
}

void MenuScene::SelectGameMode()
{
	m_selectedGameMode = std::max(0, m_selectedGameMode);
	m_selectedGameMode = std::min(1, m_selectedGameMode);
	if (m_selectedGameMode == 0)
	{
		// mode 1
		m_sbtn1.setFillColor(sf::Color(160, 32, 240));
		m_sbtn2.setFillColor(sf::Color::White);
	}
	else
	{
		// mode 2
		m_sbtn1.setFillColor(sf::Color::White);
		m_sbtn2.setFillColor(sf::Color(160, 32, 240));
	}
}

void MenuScene::update()
{
	// Render
	m_game->getWindow().clear(sf::Color::Black); // background

	m_game->getWindow().draw(m_tTitle);
	m_game->getWindow().draw(m_tMadeBy);

	m_game->getWindow().draw(m_sbtn1);
	m_game->getWindow().draw(m_tbtn1);
	m_game->getWindow().draw(m_sbtn2);
	m_game->getWindow().draw(m_tbtn2);

	m_game->getWindow().draw(m_tDescription);

	m_game->getWindow().display();
}

void MenuScene::doAction(const Action& action)
{
	if (action.type() != ActionType::Pressed) return;
	if (action.name() == ActionName::UP)
		m_selectedGameMode--;
	if (action.name() == ActionName::DOWN)
		m_selectedGameMode++;
	SelectGameMode();

	if (action.name() == ActionName::ENTER)
	{
		// change scene
		if (m_selectedGameMode == 0)
		{
			// pvp
			m_game->changeScene(SceneName::PvP);
		}
		else
		{
			// pve
			m_game->changeScene(SceneName::PvE);
		}
	}
}