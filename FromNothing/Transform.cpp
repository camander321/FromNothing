#include "Transform.h"

Transform::Transform(GameObject* p) : Component(p)
{
	name = "transform";
	D3DXMatrixIdentity(&WorldMatrix);
}


Transform::~Transform()
{
}

void Transform::Reset()
{
	D3DXMatrixIdentity(&WorldMatrix);
}

D3DXVECTOR3 Transform::GetPosition()
{
	return D3DXVECTOR3(WorldMatrix._41, WorldMatrix._42, WorldMatrix._43);
}

D3DXVECTOR3 Transform::GetForward()
{
	D3DXVECTOR4 f;
	D3DXVec4Transform(&f, &(D3DXVECTOR4(0, 0, 1, 0)), &WorldMatrix);
	return D3DXVECTOR3(f.x, f.y, f.z);
}

D3DXVECTOR3 Transform::GetBack()
{
	return -GetForward();
}

D3DXVECTOR3 Transform::GetUp()
{
	D3DXVECTOR4 f;
	D3DXVec4Transform(&f, &(D3DXVECTOR4(0, 1, 0, 0)), &WorldMatrix);
	return D3DXVECTOR3(f.x, f.y, f.z);
}

D3DXVECTOR3 Transform::GetDown()
{
	return -GetUp();
}

D3DXVECTOR3 Transform::GetRight()
{
	D3DXVECTOR4 f;
	D3DXVec4Transform(&f, &(D3DXVECTOR4(1, 0, 0, 0)), &WorldMatrix);
	return D3DXVECTOR3(f.x, f.y, f.z);
}

D3DXVECTOR3 Transform::GetLeft()
{
	return -GetRight();
}

D3DXVECTOR3 Transform::GetLookAt()
{
	return GetForward() + GetPosition();
}

D3DXMATRIX Transform::GetMatrix()
{
	return WorldMatrix;
}

void Transform::Translate(D3DXVECTOR3 v)
{
	D3DXMATRIX m;
	D3DXMatrixTranslation(&m, v.x, v.y, v.z);
	WorldMatrix = m * WorldMatrix;
}

void Transform::Translate(float x, float y, float z)
{
	D3DXMATRIX m;
	D3DXMatrixTranslation(&m, x, y, z);
	WorldMatrix = m * WorldMatrix;
}

void Transform::RotateX(float d)
{
	debug::Log("here");
	D3DXMATRIX m;
	D3DXMatrixRotationX(&m, D3DXToRadian(d));
	WorldMatrix = m * WorldMatrix;
}

void Transform::RotateY(float d)
{
	D3DXMATRIX m;
	D3DXMatrixRotationY(&m, D3DXToRadian(d));
	WorldMatrix = m * WorldMatrix;
}

void Transform::RotateZ(float d)
{
	D3DXMATRIX m;
	D3DXMatrixRotationZ(&m, D3DXToRadian(d));
	WorldMatrix = m * WorldMatrix;
}

void Transform::Scale(D3DXVECTOR3 v)
{
	D3DXMATRIX m;
	D3DXMatrixScaling(&m, v.x, v.y, v.z);
	WorldMatrix = m * WorldMatrix;
}

void Transform::Scale(float x, float y, float z)
{
	D3DXMATRIX m;
	D3DXMatrixScaling(&m, x, y, z);
	WorldMatrix = m * WorldMatrix;
}

