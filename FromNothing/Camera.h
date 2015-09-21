#pragma once

#include "Input.h"
#include "GameObject.h"

class Camera :
	public GameObject
{
public:
	Camera(GameObject* p);
	virtual ~Camera();
	float getFov();

protected:
	virtual void updateObject() override;

private:
	float fov;
	float walkspeed;
	float rotatespeed;
};

