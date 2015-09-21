#pragma once

#include <vector>
#include "MiscUtils.h"
#include "Transform.h"
#include "Component.h"

class RenderingEngine;
class GameObject
{
public:
	GameObject(GameObject* p);
	virtual ~GameObject();
	virtual void AddChild(GameObject* child) final;
	virtual void RemoveChild(GameObject* child) final;
	virtual void AddComponent(Component* component) final;
	virtual void RemoveComponent(Component* component) final;
	virtual void Update() final;
	Transform* GetTransform();

	GameObject* parent;
	Transform* transform;

protected:
	virtual void updateObject();

	char* name;
	std::vector<GameObject*> children;
	std::vector<Component*> components;
};

