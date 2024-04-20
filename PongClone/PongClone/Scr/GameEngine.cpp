#include "GameEngine.h"
#include"MenuScene.h"
#include"PvPmodeScene.h"
#include"PvEmodeScene.h"

GameEngine::GameEngine()
{
	GameInit();
}

void GameEngine::run(const SceneName& startScene)
{
	changeScene(startScene);

	while (m_window.isOpen())
	{
		UserInput();
		if (!m_isPaused && m_isFocused)
		{
			Update();
		}
	}
}

void GameEngine::GameInit()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "My Pong", sf::Style::Close, settings);
	m_window.setFramerateLimit(m_fps);
	m_window.setKeyRepeatEnabled(false);
	m_assets.loadAssets("Resources/Assets.txt");
	//m_window.setMouseCursorVisible(false);
}

void GameEngine::Update()
{
	m_currentScene->update();
}

void GameEngine::UserInput()
{
	// check all the window's events that were triggered since the last iteration of the loop
	while (m_window.pollEvent(m_input))
	{
		if (m_input.type == sf::Event::Closed)
			m_window.close();

		switch (m_input.type)
		{
		case sf::Event::KeyPressed:
			if (m_input.key.scancode == sf::Keyboard::Scan::P) // Pause
				m_isPaused = !m_isPaused;
			KeyInput(true);
			break;
		case sf::Event::KeyReleased:
			KeyInput(false);
			break;
		case sf::Event::MouseButtonPressed:
			break;
		case sf::Event::LostFocus:
			m_isFocused = false;
			break;
		case sf::Event::GainedFocus:
			m_isFocused = true;
			break;
		default:
			break;
		}
	}
}

void GameEngine::KeyInput(bool isPressed)
{
	if (m_isPaused || !m_isFocused) return;
	if (m_currentScene->getActionMap().find(m_input.key.code) == m_currentScene->getActionMap().end()) return;

	ActionType actionType = isPressed ? ActionType::Pressed : ActionType::Released;
	m_currentScene->doAction(Action(m_currentScene->getActionMap().at(m_input.key.code), actionType));
}

void GameEngine::changeScene(const SceneName& sceneName)
{
	m_currentSceneName = sceneName;
	switch (m_currentSceneName)
	{
	case SceneName::Menu:
		m_currentScene = std::make_shared<MenuScene>(this);
		break;
	case SceneName::PvP:
		m_currentScene = std::make_shared<PvPmodeScene>(this);
		break;
	case SceneName::PvE:
		m_currentScene = std::make_shared<PvEmodeScene>(this);
		break;
	default:
		break;
	}
}

sf::RenderWindow& GameEngine::getWindow()
{
	return m_window;
}

AssetLoader& GameEngine::getAssets()
{
	return m_assets;
}

unsigned GameEngine::windowHeight() const
{
	return m_windowHeight;
}

unsigned GameEngine::windowWidth() const
{
	return m_windowWidth;
}

int GameEngine::getFps() const
{
	return m_fps;
}