//#include "Game\TheGame.h"

#pragma comment(lib, "CPlusEngine.lib")
#include "TheGame/TheGame.h"

// Nice and simple encapsolation of my game

int main(int argv, char *argc[])
{
	int retVal = -1;

	DemoGame::TheGame game;

	game.Init();
	if (game.IsReady())
	{
		game.LoadScene(1);
		retVal = game.Run();
	}

	// Exit program
	return retVal;
}
