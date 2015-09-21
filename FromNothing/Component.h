#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "MiscUtils.h"

class GameObject;
class Component
{
public:
	Component(GameObject* p);
	virtual ~Component();
	virtual void Init();
	virtual void Update();

	std::string name;
	GameObject* parent;

protected:
	bool initialized;
};

namespace ComponentRegistry {
	void AddComponent(Component* c);
	std::vector<Component*>* getList(std::string name);
	void LogListSize(char* name);
	extern std::unordered_map<std::string, std::vector<Component*>*> compMap;
};