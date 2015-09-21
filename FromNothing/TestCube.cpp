#include "TestCube.h"



TestCube::TestCube(GameObject* p) : GameObject(p)
{
	MeshRenderer* mr = new MeshRenderer(this);
	mr->Init();
	AddComponent(mr);
}


TestCube::~TestCube()
{
}

void TestCube::updateObject()
{

}
