#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	renderingEngine->CleanD3D();
	delete renderingEngine;
	renderingEngine = NULL;

	delete root;
	root = NULL;
}

#define NUMCUBES 1

void Game::init()
{
	root = new GameObject(NULL);
	GameObject* cubes[NUMCUBES];
	for (int i = 0; i < NUMCUBES; i++) {
		if (i == 0) {
			cubes[i] = new TestCube(root);
			root->AddChild(cubes[i]);
		}
		else {
			cubes[i] = new TestCube(cubes[i - 1]);
			cubes[i-1]->AddChild(cubes[i]);
		}
	}

	Camera* camera = new Camera(root);

	renderingEngine->SetMainCamera(camera);
	root->AddChild(camera);

	std::vector<Component*>* renderables = ComponentRegistry::getList("renderable");
	if (renderables) {
		for (int i = 0; i < renderables->size(); i++) {
			if (renderables->at(i) == NULL) {
				renderables->erase(renderables->begin() + i);
				i--;
			}
			else {
				((Renderable*)renderables->at(i))->InitRendering(renderingEngine);
			}
		}
	}
}

void Game::SetRenderingEngine(RenderingEngine * r)
{
	renderingEngine = r;
}

void Game::SetWindowTitle(char * t)
{
	renderingEngine->SetTitleBar(t);
}

void Game::ShowFPSInTitle(int fps)
{
	renderingEngine->ShowFpsInTitle(fps);
}

bool Game::isCloseRequested()
{
	return closeRequested;
}

void Game::Update()
{
	input::Update();
	root->Update();
	closeRequested = renderingEngine->GetQuitMsg();
}

void Game::Render()
{
	std::vector<Component*>* renderables = ComponentRegistry::getList("renderable");
	if (renderables) {
		for (int i = 0; i < renderables->size(); i++) {
			if (renderables->at(i) == NULL) {
				renderables->erase(renderables->begin() + i);
				i--;
			}
			else {
				((Renderable*)renderables->at(i))->Render(renderingEngine);
			}
		}
	}
	renderingEngine->SwapBuffers();
}


