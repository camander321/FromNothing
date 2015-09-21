#pragma once

#include "GameObject.h"
#include "MeshRenderer.h"

class TestCube :
	public GameObject
{
public:
	TestCube(GameObject* p);
	virtual ~TestCube();

protected:
	virtual void updateObject() override;
};

