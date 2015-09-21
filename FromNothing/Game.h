#pragma once

#include <vector>
#include "GameObject.h"
#include "TestCube.h"
#include "Camera.h"

#include "Input.h"
#include "Component.h"
#include "Renderable.h"
#include "RenderingEngine.h"

class Game
{
public:
	Game();
	virtual ~Game();
	virtual void init();
	void SetRenderingEngine(RenderingEngine* r);
	void SetWindowTitle(char* t);
	void ShowFPSInTitle(int fps);
	bool isCloseRequested();
	virtual void Update() final;
	virtual void Render() final;


private:
	RenderingEngine* renderingEngine;
	GameObject* root;

	bool closeRequested;
};

