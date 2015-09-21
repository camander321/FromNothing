#pragma once

#include "Renderable.h"
#include "Mesh.h"


class MeshRenderer : public Renderable
{
public:
	MeshRenderer(GameObject* p);
	~MeshRenderer();

	virtual void renderComponent(RenderingEngine* renderingEngine) override;
	virtual void InitRendering(RenderingEngine* renderingEngine) override;

private:
	Mesh* mesh;
	int indexBase;
	int vertBase;

};

