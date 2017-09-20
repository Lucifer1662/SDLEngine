#include "_MeshLoaded.h"
#include "Engine.h"



_MeshLoaded::~_MeshLoaded()
{	
	this->RemoveFromGPU();
}

void _MeshLoaded::RemoveFromGPU()
{
	glDeleteBuffers(buffers.size(), &buffers[0]);
}