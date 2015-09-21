#pragma once

#include "Timer.h"
#include "RenderingEngine.h"
#include "Game.h"
#include "MiscUtils.h"

struct GameConfigs
{
	char* Title = "Cam's Game Engine";
	Game *game = NULL;
	UINT FrameRate = 30;
	UINT ScreenWidth = 400;
	UINT ScreenHeight = 300;
	bool FullScreen = false;
};

class Engine
{
public:
	Engine();
	~Engine();
	int Run(HINSTANCE hInstance, int nCmdShow);
	int Run(HINSTANCE hInstance, int nCmdShow, struct GameConfigs gc);
	void Stop();

private:
	void init(HINSTANCE hInstance, int nCmdShow, GameConfigs gc);
	void mainLoop(UINT FrameRate);
	void cleanup();

	void render();
	void update();

	Game *game;
	bool running;
};

