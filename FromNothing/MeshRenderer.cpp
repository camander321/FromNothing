#include "MeshRenderer.h"



MeshRenderer::MeshRenderer(GameObject* p) : Renderable(p)
{
	mesh = new Mesh("resources/sphere.obj");
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::renderComponent(RenderingEngine * renderingEngine)
{
	renderingEngine->RenderIndexedVerts(parent->GetTransform()->GetMatrix(), mesh->indices.size(), mesh->indexOffset, mesh->vertOffset);
}

void MeshRenderer::InitRendering(RenderingEngine* renderingEngine)
{
	mesh->init(renderingEngine);
}
