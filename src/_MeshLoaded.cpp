#include "_MeshLoaded.h"
#include "Engine.h"



_MeshLoaded::~_MeshLoaded()
{	
	this->RemoveFromGPU();
}

void _MeshLoaded::RemoveFromGPU()
{
	std::cout << name << std::endl;
	for (size_t i = 0; i < buffers.size(); i++)
	{
		std::cout << buffers[i] << std::endl;
	}
	glDeleteBuffers(buffers.size(), &buffers[0]);
}