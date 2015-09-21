#include "Engine.h"

Engine::Engine()
{
	running = false;
}

Engine::~Engine(){}

int Engine::Run(HINSTANCE hInstance, int nCmdShow)
{
	GameConfigs gc;
	gc.game = new Game();
	return Run(hInstance, nCmdShow, gc);
}

int Engine::Run(HINSTANCE hInstance, int nCmdShow, struct GameConfigs gc)
{
	if (running == false)
	{
		running = true;
		game = gc.game;
		init(hInstance, nCmdShow, gc);
		mainLoop(gc.FrameRate);
		cleanup();
		return 0;
	}
	return 1;
}

void Engine::Stop()
{
	running = false;
}

void Engine::init(HINSTANCE hInstance, int nCmdShow, GameConfigs gc)
{
	//renderingEngine->
	RenderingEngine* renderingEngine = new RenderingEngine(hInstance, nCmdShow, gc.Title, gc.ScreenWidth, gc.ScreenHeight, gc.FullScreen);
	gc.game->SetRenderingEngine(renderingEngine);
	gc.game->init();
}

void Engine::mainLoop(UINT Framerate)
{
	Timer time;
	double timeStep = time.SECOND / Framerate;
	double elapsedTime = 0;
	double frameCounterTime = 0;
	int frameCount = 0;

	bool needsRender = false;
	while (running)
	{
		time.updateDelta();
		elapsedTime += time.getDelta();
		frameCounterTime += time.getDelta();

		while (elapsedTime >= timeStep && running) {
			elapsedTime -= timeStep;
			update();
			needsRender = true;
			if (elapsedTime > time.SECOND) {
				elapsedTime = 0;
				debug::Log("Frame Skip");
			}
		}

		if (needsRender) {
			render();
			needsRender = false;
			frameCount++;
		}

		if (frameCounterTime >= time.SECOND) {
			game->ShowFPSInTitle(frameCount);
			frameCount = 0;
			frameCounterTime -= time.SECOND;
		}
	}
}

void Engine::cleanup()
{
	delete game;
	game = NULL;
}

void Engine::update()
{
	if (game->isCloseRequested())
		Stop();
	game->Update();
}

void Engine::render()
{
	game->Render();
}


