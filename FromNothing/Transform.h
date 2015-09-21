#pragma once

#include <d3dx9math.h>
#include <DirectXMath.h>

#include "Component.h"

class Transform : public Component
{
public:
	Transform(GameObject* p);
	~Transform();

	D3DXMATRIX WorldMatrix;

	void Reset();
	D3DXVECTOR3 GetPosition();

	D3DXVECTOR3 GetForward();
	D3DXVECTOR3 GetBack();
	D3DXVECTOR3 GetUp();
	D3DXVECTOR3 GetDown();
	D3DXVECTOR3 GetRight();
	D3DXVECTOR3 GetLeft();

	D3DXVECTOR3 GetLookAt();
	D3DXMATRIX GetMatrix();

	void Translate(D3DXVECTOR3 v);
	void Translate(float x, float y, float z);

	void RotateX(float d);
	void RotateY(float d);
	void RotateZ(float d);

	void Scale(D3DXVECTOR3 v);
	void Scale(float x, float y, float z);
};

