#pragma once

#include "Component.h"
#include "RenderingEngine.h"

class Renderable : public Component
{
public:
	Renderable(GameObject* p);
	virtual ~Renderable();
	virtual void InitRendering(RenderingEngine* renderingEngine);
	virtual void Render(RenderingEngine* renderingEngine) final;

protected:
	virtual void renderComponent(RenderingEngine* renderingEngine);

	bool renderingInitialized;
};

