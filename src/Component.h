#pragma once
#include "API.h"

class Entity;
struct API Component {
public:
	Entity* entity;
	virtual void Update() {};
	virtual void Render() {};
	virtual void Start() {};
	virtual ~Component() {};

};