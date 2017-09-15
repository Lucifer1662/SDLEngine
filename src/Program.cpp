#include "Program.h"
#include <iostream>
#include <vector>
#include "ReadFiles.h"
#include <exception>
#include "Engine.h"
#define WINDOWS
using std::cout;
using std::endl;

vector<Program*> Program::programs;

Program::Program(): program(_program) {}

  
Program::~Program() {
	glUseProgram(0);
	glDeleteProgram(program);
}

GLuint Program::CreateProgram() {
	return 0;
};

void Program::Use() {
	glUseProgram(_program);
}

GLuint Program::_CreateProgram(vector<ShaderSource> sources) {
	_program = glCreateProgram();

	GLuint* shaderIds = new GLuint[sources.size()];
	for (size_t i = 0; i < sources.size(); i++)
	{
		string source = "";
#ifdef  WINDOWS
		source = "#version 330 core";
#else
		source = "#version 300 es";
#endif //  WINDOWS
	
		source.append(ReadFile(sources[i].filePath));
		shaderIds[i] = CreateShader(sources[i].shaderType, source);
		glAttachShader(program, shaderIds[i]);
	}
	
	
	glLinkProgram(program);

	int InfoLogLength;
	GLint Result = GL_FALSE;
	// Check the program
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 1) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	for (size_t i = 0; i < sources.size(); i++)
	{
		glDetachShader(program, shaderIds[i]);
		glDeleteShader(shaderIds[i]);
	}
	delete[] shaderIds;
	cout << "Program Created" << endl;
	return program;
}


GLuint Program::CreateShader(GLenum type, string source) {

	GLuint shader = glCreateShader(type);
	const GLchar* chars = source.c_str();
	glShaderSource(shader, 1, &chars, NULL);
	glCompileShader(shader);
	GLint isCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		 
		//The maxLength includes the NULL character
		GLchar* infoLog = new GLchar[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
		//We don't need the shader anymore.
 		glDeleteShader(shader);
		cout << maxLength << endl;
		cout << "-----------------------------------------" << endl;
		cout << infoLog << endl;
		cout << "-----------------------------------------" << endl;
		return 0;
	}

	return shader;
}

void Program::TermaniteAllPrograms() {
	for (size_t i = 0; i < programs.size(); i++)
	{
		delete programs[i];
	}
	programs.resize(0);
}
