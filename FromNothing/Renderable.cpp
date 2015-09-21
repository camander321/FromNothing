#include "Renderable.h"



Renderable::Renderable(GameObject* p) : Component(p)
{
	name = "renderable";
	renderingInitialized = false;
}


Renderable::~Renderable()
{
}

void Renderable::InitRendering(RenderingEngine * renderingEngine)
{
}

void Renderable::Render(RenderingEngine* renderingEngine)
{
	if (!renderingInitialized) {
		InitRendering(renderingEngine);
		renderingInitialized = true;
	}
	renderComponent(renderingEngine);
}

void Renderable::renderComponent(RenderingEngine * renderingEngine)
{
}
