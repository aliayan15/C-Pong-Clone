#pragma once
#include "SFML/Graphics.hpp"
#include<iostream>

#include "Action.h"
#include "Scene.h"
#include"AssetLoader.h"

enum class SceneName
{
	Menu,
	PvP,
	PvE
};

class GameEngine
{
public:
	GameEngine();
	void run(const SceneName& startScene);
	void changeScene(const SceneName& sceneName);
	sf::RenderWindow& getWindow();
	AssetLoader& getAssets();
	const unsigned windowHeight() const;
	const unsigned windowWidth() const;
	const int getFps() const;

private:
	void GameInit();
	void Update();
	void UserInput();
	void KeyInput(bool isPressed);

private:
	sf::RenderWindow m_window;
	SceneName m_currentSceneName = SceneName::Menu;
	std::shared_ptr<SceneBase> m_currentScene = nullptr;
	AssetLoader m_assets;
	unsigned m_windowHeight = 500;
	unsigned m_windowWidth = 800;
	bool m_isPaused = false;
	bool m_isFocused = true;
	int m_fps = 60;
	sf::Event m_input;
};
