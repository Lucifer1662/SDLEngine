#pragma once
#include "API.h"
#include <vector>
#include "Component.h"
#include "Transform.h"
using std::vector;

class Engine;
class API Entity
{
	friend class Engine;	
	vector<Component*> components;
	void Update();
	void Render();
	void Start();
	
public:
	Entity(Engine* engine);
	Entity(size_t numOfComponents);
	~Entity();
	Engine* engine;
	Transform transform;

	template<typename T>
	T* AddComponent() {
		T* t = new T();
		((Component*)t)->entity = this;
		components.push_back((Component*)t);
		return t;
	}
};

