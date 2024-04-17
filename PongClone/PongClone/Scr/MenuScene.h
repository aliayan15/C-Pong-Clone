#pragma once
#include "GameEngine.h"

class MenuScene :public SceneBase
{
public:
	MenuScene(GameEngine* game);

private:
	void init();
	void InitOptions(sf::RectangleShape& s, sf::Text& t, float y, const char* text);
	void SelectGameMode();

	// Inherited via SceneBase
	void update() override;
	void doAction(const Action& action) override;

private:
	sf::Font m_tekoFont;
	sf::Vector2u m_windowSize;
	sf::Text m_tTitle;
	sf::Text m_tMadeBy;
	sf::RectangleShape m_sbtn1;
	sf::RectangleShape m_sbtn2;
	sf::Text m_tbtn1;
	sf::Text m_tbtn2;
	sf::Text m_tDescription;
	int m_selectedGameMode = 0;
};
