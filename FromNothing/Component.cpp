#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* p)
{
	name = "empty";
	parent = p;
}

Component::~Component()
{
}

void Component::Init()
{
	initialized = true;
	ComponentRegistry::AddComponent(this);
}

void Component::Update()
{

}

void ComponentRegistry::AddComponent(Component* c)
{
	auto it = compMap.find(c->name);
	if (it != compMap.end())
		it->second->push_back(c);
	else {
		std::vector<Component*>* newVec = new std::vector<Component*>();
		newVec->push_back(c);
		compMap.emplace(c->name, newVec);
	}
}

std::vector<Component*>* ComponentRegistry::getList(std::string name)
{
	auto it = compMap.find(name);
	if (it == compMap.end()) {
		return NULL;
	}
	return it->second;
}

void ComponentRegistry::LogListSize(char* name) {
	std::vector<Component*>* type = ComponentRegistry::getList(name);
	if (type) debug::Log((int)type->size());
	else debug::Log(std::string("no ") + name);
}

std::unordered_map<std::string, std::vector<Component*>*> ComponentRegistry::compMap;
