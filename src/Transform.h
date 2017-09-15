#pragma once
#include "API.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Component.h"
using glm::vec3;
using glm::mat4;
class API Transform : public Component
{
	
public:
	Transform();
	~Transform();
	vec3 position;
	vec3 rotation;
	vec3 scale;
	mat4 translationMatrix, rotationMatrix, scaleMatrix;
	void SetPosition(vec3 position) {
		this->position = position;
		translationMatrix = glm::translate(position);
	}
	void SetRotation(vec3 rotation) {
		this->rotation = rotation;
		rotationMatrix = glm::rotate(rotation.x, vec3(1, 0, 0))
			* glm::rotate(rotation.y, vec3(0, 1, 0))
			* glm::rotate(rotation.z, vec3(0, 0, 1));
	}
	void SetScale(vec3 scale) {
		this->scale = scale;
		scaleMatrix = glm::scale(scale);
	}
	
};

