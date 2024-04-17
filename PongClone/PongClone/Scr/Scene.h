#pragma once
#include <unordered_map>
#include "Action.h"
#include "SFML/Graphics.hpp"

class GameEngine;

class SceneBase
{
public:
	SceneBase();
	SceneBase(GameEngine* game);

	/// <summary>
	/// Update is called in every frame.
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// DoAction is called when there is a user input before update.
	/// </summary>
	/// <param name="action"></param>
	virtual void doAction(const Action& action) = 0;
	/// <summary>
	/// Register new action for a key.
	/// </summary>
	/// <param name="key"></param>
	/// <param name="actionName"></param>
	void registerAction(const int key, const ActionName actionName);
	/// <summary>
	/// Remove action with a key.
	/// </summary>
	/// <param name="key"></param>
	void removeAction(const int key);
	const std::unordered_map<int, ActionName>& getActionMap() const;

protected:
	void InitText(sf::Text& t, const std::string& text, unsigned int size,
		const sf::Color& color, bool isBold, sf::Vector2f pos, sf::Font& font);

protected:
	GameEngine* m_game = nullptr;
	std::unordered_map<int, ActionName> m_actionMap;
};

