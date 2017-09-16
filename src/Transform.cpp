#include "Transform.h"



void Transform::Start()
{
	RecalulateOverallTransform();
}

Transform::Transform()
{
}


Transform::~Transform()
{
}

void Transform::RecalulateOverallTransform()
{
	overallTransform = translationMatrix * rotationMatrix * scaleMatrix;
	if(entity->GetParent() != nullptr)
		overallTransform = entity->GetParent()->transform->overallTransform * translationMatrix * rotationMatrix * scaleMatrix;


	for (size_t i = 0; i < entity->ChildCount(); i++)
		entity->GetChildAt(i)->transform->RecalulateOverallTransform();
}

