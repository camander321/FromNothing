#include "GameObject.h"

GameObject::GameObject(GameObject* p)
{
	name = "empty object";
	parent = p;
	transform = new Transform(this);
	transform->Init();
	AddComponent(transform);
}

GameObject::~GameObject()
{
	delete transform;
	for (int i = 0; i < (int)children.size(); i++)
	{
		delete children[i];
		children[i] = NULL;
	}
}

void GameObject::AddChild(GameObject* child)
{
	children.push_back(child);
}

void GameObject::RemoveChild(GameObject* child)
{
	for (int i = 0; i < (int)children.size(); i++)
	{
		if (children[i] == child) {
			delete children[i];
			children.erase(children.begin() + i);
			break;
		}
	}
}

void GameObject::AddComponent(Component * component)
{
	components.push_back(component);
}

void GameObject::RemoveComponent(Component * component)
{
	for (int i = 0; i < (int)components.size(); i++)
	{
		if (components[i] == component) {
			delete components[i];
			components.erase(components.begin() + i);
			break;
		}
	}
}

void GameObject::Update()
{
	updateObject();

	for (int i = 0; i < (int)components.size(); i++)
	{
		if (components[i]) components[i]->Update();
		else {
			components.erase(components.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < (int)children.size(); i++)
	{
		if (children[i]) children[i]->Update();
		else{
			children.erase(children.begin() + i);
			i--;
		}
	}
}

Transform* GameObject::GetTransform()
{
	return transform;
}

void GameObject::updateObject()
{
}
