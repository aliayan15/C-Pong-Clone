#include "PongGame.h"


PongGame::PongGame()
{
}

void PongGame::startGame()
{
	GameEngine game;
	game.run(SceneName::Menu);
}


