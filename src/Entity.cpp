#include "Entity.h"
#include "Transform.h"
#include "Component.h"


void Entity::Update()
{
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Update();
}

void Entity::Render()
{
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Render();
}

void Entity::Start()
{
	for (size_t i = 0; i < components.size(); i++)
		components[i]->Start();
	
}

Entity::Entity(Engine* engine): engine(engine)
{
	transform.entity = this;
	components.push_back((Component*)&transform);
}

Entity::Entity(size_t numOfComponents)
{
}


Entity::~Entity()
{
}
