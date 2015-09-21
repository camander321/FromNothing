#include "Mesh.h"

Mesh::Mesh()
{
	verts =
	{
		{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },    // side 1
		{ 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },

		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },    // side 2
		{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f },
		{ 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f },

		{ -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },    // side 3
		{ -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f },

		{ -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f },    // side 4
		{ 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f },
		{ 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f },

		{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },    // side 5
		{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f },

		{ -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f },    // side 6
		{ -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f },
	};

	indices =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 5, 6,    // side 2
		6, 5, 7,
		8, 9, 10,    // side 3
		10, 9, 11,
		12, 13, 14,    // side 4
		14, 13, 15,
		16, 17, 18,    // side 5
		18, 17, 19,
		20, 21, 22,    // side 6
		22, 21, 23,
	};
}

Mesh::Mesh(std::string filename)
{
	LoadOBJ(filename);
}

Mesh::~Mesh()
{
}

void Mesh::init(RenderingEngine * renderingEngine)
{
	renderingEngine->UpdateVertexBuffer(verts.data(), verts.size());
	renderingEngine->UpdateIndexBuffer(indices.data(), indices.size());
}

void Mesh::LoadOBJ(std::string filename)
{

	struct FACE {
		unsigned int v0, v1, v2, t0, t1, t2, n0, n1, n2;
	};

	std::vector<FACE> faces;
	std::vector<D3DXVECTOR3> vertVec;
	std::vector<D3DXVECTOR3> normVec;
	std::vector<D3DXVECTOR2> txtrVec;

	FILE * file;
	fopen_s(&file, filename.c_str(), "r");
	if (file == NULL) {
		return;
	}

	while (true) {

		char lineHeader[128];
		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0) {
			D3DXVECTOR3 v;
			fscanf_s(file, "%f %f %f\n", &v.x, &v.y, &v.z);
			vertVec.push_back(v);
		}

		else if (strcmp(lineHeader, "vn") == 0) {
			D3DXVECTOR3 n;
			fscanf_s(file, "%f %f %f\n", &n.x, &n.y, &n.z);
			normVec.push_back(n);
		}

		else if (strcmp(lineHeader, "vt") == 0) {
			D3DXVECTOR2 t;
			fscanf_s(file, "%f %f\n", &t.x, &t.y);
			txtrVec.push_back(t);
		}

		else if (strcmp(lineHeader, "f") == 0) {
			FACE f;
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &f.v0, &f.t0, &f.n0, &f.v1, &f.t1, &f.n1, &f.v2, &f.t2, &f.n2);
			if (matches != 9) {
				return;
			}
			faces.push_back(f);
		}
	}

	D3DXVECTOR3 v;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;
	for (unsigned int i = 0; i < faces.size(); i++) {

		v = vertVec[faces[i].v0 - 1];
		n = normVec[faces[i].n0 - 1];
		t = txtrVec[faces[i].t0 - 1];
		verts.push_back({ v.x, v.y, v.z, n.x, n.y, n.z, t.x, t.y });
		indices.push_back(i * 3 + 0);

		v = vertVec[faces[i].v1 - 1];
		n = normVec[faces[i].n1 - 1];
		t = txtrVec[faces[i].t1 - 1];
		verts.push_back({ v.x, v.y, v.z, n.x, n.y, n.z, t.x, t.y });
		indices.push_back(i * 3 + 1);

		v = vertVec[faces[i].v2 - 1];
		n = normVec[faces[i].n2 - 1];
		t = txtrVec[faces[i].t2 - 1];
		verts.push_back({ v.x, v.y, v.z, n.x, n.y, n.z, t.x, t.y });
		indices.push_back(i * 3 + 2);
	}
}
