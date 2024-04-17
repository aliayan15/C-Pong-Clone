#include "Scene.h"


SceneBase::SceneBase()
{
}

SceneBase::SceneBase(GameEngine* game) :m_game(game)
{
}

void SceneBase::registerAction(const int key, const ActionName actionName)
{
	m_actionMap[key] = actionName;
}

void SceneBase::removeAction(const int key)
{
	m_actionMap.erase(key);
}

const std::unordered_map<int, ActionName>& SceneBase::getActionMap() const
{
	return m_actionMap;
}

void SceneBase::InitText(sf::Text& t, const std::string& text, unsigned int size, const sf::Color& color, bool isBold, sf::Vector2f pos, sf::Font& font)
{
	t.setFont(font);
	t.setString(text);
	t.setCharacterSize(size);
	t.setFillColor(color);
	if (isBold)
		t.setStyle(sf::Text::Bold);
	auto titleBound = t.getGlobalBounds();
	t.setOrigin(sf::Vector2f(titleBound.width / 2, 0));
	t.setPosition(pos.x, pos.y);
}
