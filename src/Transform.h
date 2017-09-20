#pragma once
#include "API.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Component.h"
#include <Entity.h>
using glm::vec3;
using glm::mat4;
class API Transform : public Component
{

	void RecalulateOverallTransform();
public:
	void Start();
	Transform();
	~Transform();
	vec3 position;
	vec3 rotation;
	vec3 scale;
	mat4 translationMatrix, rotationMatrix, scaleMatrix, overallTransform;
	void SetPosition(vec3 position) {
		this->position = position;
		translationMatrix = glm::translate(position);
		RecalulateOverallTransform();
	}
	void SetRotation(vec3 rotation) {
		rotation = glm::radians(rotation);
		this->rotation = rotation;
		rotationMatrix = glm::rotate(rotation.x, vec3(1, 0, 0))
			* glm::rotate(rotation.y, vec3(0, 1, 0))
			* glm::rotate(rotation.z, vec3(0, 0, 1));
		RecalulateOverallTransform();
	}
	void SetScale(vec3 scale) {
		this->scale = scale;
		scaleMatrix = glm::scale(scale);
		RecalulateOverallTransform();
	}

	void AddPosition(vec3 position) {
		SetPosition(this->position + position);
	}

	void AddRotation(vec3 rotation) {
		SetRotation(this->rotation + rotation);
	}

	void AddScale(vec3 scale) {
		SetScale(this->scale + scale);
	}



	
};

