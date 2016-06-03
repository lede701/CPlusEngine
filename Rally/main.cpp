#include "stdafx.h"
#include "Game/TheGame.h"

#pragma comment(lib, "CPlusEngine.lib")

int main(int argc, char *argv[])
{
	int retval = -1;

	Rally::TheGame game;
	game.Init();
	if (game.IsReady())
	{
		game.MainMenu();
		retval = game.Run();
	}

	return retval;
}