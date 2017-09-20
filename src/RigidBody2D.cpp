#include "RigidBody2D.h"
#include "EngineTime.h"


RigidBody2D::RigidBody2D()
{
}


RigidBody2D::~RigidBody2D()
{
}


void RigidBody2D::Update()
{
	velocity += acceleration * (float)EngineTime::deltaTime;
	entity->transform->AddPosition(velocity * (float)EngineTime::deltaTime);

	angularAcceleration += angularAcceleration * (float)EngineTime::deltaTime;
	entity->transform->AddPosition(angularVelocity * (float)EngineTime::deltaTime);
	AddForce(-velocity*drag*(float)EngineTime::deltaTime);
	AddForce(vec3(0, -gravity * EngineTime::deltaTime, 0));
}

void RigidBody2D::AddForce(vec3 force)
{
	//f = ma;
	//a = f/m
	acceleration += force / mass;
}
