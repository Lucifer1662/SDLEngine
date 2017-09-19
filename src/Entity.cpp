#include "Entity.h"
#include "Transform.h"
#include "Component.h"
#include "Engine.h"


void Entity::Update()
{
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Update();
	for (size_t i = 0; i < children.size(); i++)
		children[i]->Update();
}

void Entity::Render()
{
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Render();
	for (size_t i = 0; i < children.size(); i++)
		children[i]->Render();
}

void Entity::Start()
{
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Start();
	for (size_t i = 0; i < children.size(); i++)
		children[i]->Start();
	
}

Entity::Entity()
{
	transform = new Transform();
	transform->entity = this;
	components.push_back((Component*)transform);
}

Entity::Entity(size_t numOfComponents)
{
}


Entity::~Entity()
{
	for (size_t i = 0; i < components.size(); i++)
		delete components[i];
	
	components.clear();
	for (size_t i = 0; i < children.size(); i++)
		delete children[i];
	
	children.clear();
}

Entity * Entity::AddChild(Entity * child)
{
	for (size_t i = 0; i < children.size(); i++)
		if (children[i] == child)
			return nullptr;

	children.push_back(child);
	return child;
}

Entity * Entity::SetParent(Entity * parent)
{
	if (parent == nullptr)
		Engine::entities.push_back(parent);
	else {
		this->parent = parent;
		parent->AddChild(this);
		for (size_t i = 0; i < Engine::entities.size(); i++)
		{
			if (Engine::entities[i] == this) {
				Engine::entities[i] = Engine::entities[Engine::entities.size() - 1];
				Engine::entities.pop_back();
				return parent;
			}
		}
	}
	
	return parent;
}

Entity * Entity::GetParent()
{
	return parent;
}

void Entity::RemoveChild(Entity * child)
{
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i] == child)
		{
			children[i] = children[children.size() - 1];
			children.pop_back();
			return;
		}
	}
}

Entity * Entity::GetChildAt(size_t index)
{
	if (index > children.size() - 1)
		return nullptr;
	return children[index];
}

size_t Entity::ChildCount()
{
	return children.size();
}

vector<Entity*> Entity::getCopyOfChildren()
{
	return children;
}

void Entity::Destroy()
{
	Engine::DestroyEntity(this);
}
