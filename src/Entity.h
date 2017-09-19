#pragma once
#include "API.h"
#include <vector>
#include "Component.h"
#include "Transform.h"
using std::vector;

class Transform;
class Engine;
class API Entity
{
	friend class Engine;	
	vector<Component*> components;
	void Update();
	void Render();
	void Start();
	
	vector<Entity*> children;
	Entity* parent;

public:
	Entity();
	Entity(size_t numOfComponents);
	~Entity();
	Transform* transform;

	template<typename T>
	T* AddComponent() {
		T* t = new T();
		((Component*)t)->entity = this;
		components.push_back((Component*)t);
		return t;
	}

	Entity* AddChild(Entity* child);
	Entity* SetParent(Entity* parent);
	Entity* GetParent();
	void RemoveChild(Entity* child);
	Entity* GetChildAt(size_t index);
	size_t ChildCount();
	vector<Entity*> getCopyOfChildren();
	void Destroy();

	
};

