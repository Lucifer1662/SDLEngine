#pragma once
#include <string>
#include <GL\glew.h>
using std::string;


std::string ReadFile(string filePath);
void ReadFile(void* buffer, GLuint bytesize, GLuint length, string fileFullPath);

