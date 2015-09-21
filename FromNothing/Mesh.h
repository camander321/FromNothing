#pragma once

#include "Vertex.h"
#include "RenderingEngine.h"
#include "MiscUtils.h"

class Mesh
{
public:
	Mesh();
	Mesh(std::string file);
	~Mesh();
	void init(RenderingEngine* renderingEngine);

	int vertOffset;
	int indexOffset;

	std::vector<VERTEX> verts;
	std::vector<DWORD> indices;

private:
	void LoadOBJ(std::string filename);

	bool initialized;
};

