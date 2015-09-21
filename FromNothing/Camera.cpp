#include "Camera.h"



Camera::Camera(GameObject* p) : GameObject(p)
{
	name = "camera";
	fov = 45;
	walkspeed = 0.1f;
	rotatespeed = 2.0f;
}

Camera::~Camera()
{
}

float Camera::getFov()
{
	return fov;
}

void Camera::updateObject()
{
	{
		static float x, y;
		x = 0;
		y = 0;
		if (input::GetKeyDown('W'))
			y += walkspeed;
		if (input::GetKeyDown('A'))
			x -= walkspeed;
		if (input::GetKeyDown('S'))
			y -= walkspeed;
		if (input::GetKeyDown('D'))
			x += walkspeed;
		if (x && y) {
			x *= 0.707f;
			y *= 0.707f;
		}
		if (x || y)
			transform->Translate(x, 0, y);
		if (input::GetKeyDown(' '))
			transform->Translate(0, walkspeed, 0);
		if (input::GetKeyDown('V'))
			transform->Translate(0, -walkspeed, 0);
	}

	{
		if (input::GetKeyDown('J'))
			transform->RotateY(-rotatespeed);
		if (input::GetKeyDown('L'))
			transform->RotateY(rotatespeed);
	}
}
