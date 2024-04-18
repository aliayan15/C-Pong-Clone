#pragma once
#include "PvPmodeScene.h"

class PvEmodeScene:public PvPmodeScene
{
public:
	PvEmodeScene(GameEngine* game);

private:
	void init();
	// Inherited via SceneBase
	void update() override;
	void doAction(const Action& action) override;

	void registerPlayerInputs() override;
	void render() override;
	void updateScore() override;
	
private:
	bool m_isAIchangedMoveDir = false;
	sf::Clock m_AIclock;
};

