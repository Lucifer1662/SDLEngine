#pragma once
#include "API.h"
#include "Component.h"
#include "glm\glm.hpp"
#include "Transform.h"
using glm::vec3;
class API RigidBody2D :	public Component
{
	vec3 velocity, acceleration, angularVelocity, angularAcceleration;
public:
	float gravity = 0.8f, mass = 1, drag = 0.1f;
	RigidBody2D();
	~RigidBody2D();
	void Update();
	void AddForce(vec3 force);
};

