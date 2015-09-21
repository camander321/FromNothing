#include "Engine.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	GameConfigs gc;
	ZeroMemory(&gc, sizeof(GameConfigs));
	gc.Title = "Test Game";
	gc.game = new Game();
	gc.FrameRate = 60;
	gc.ScreenWidth = 800;
	gc.ScreenHeight = 600;
	gc.FullScreen = false;

	Engine engine;
	return engine.Run(hInstance, nCmdShow, gc);
}

