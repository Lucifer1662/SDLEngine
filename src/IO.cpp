#include "IO.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Window.h"

using std::ifstream;
using std::string;



std::istream* openStringStream(void*& file, const char * filename, int& error) {
	error = open(file, filename);
	return new ifstream((FILE*)file);	 
}

int closeStringStream(void* file) {
	return close(file);
}

int open(void*& file, const char * filename) {
	FILE* f = (FILE*)file;
	string filepath = Engine::localFilePath;
	filepath.append(filename);
	int w = fopen_s(&f, filepath.c_str(), "rb");
	file = f;
	return w;
	
}
int read(void* buffer, size_t size, size_t length, void* file) {
	return fread(buffer, size, length, (FILE*)file);
}
int close(void* file) {
	return fclose((FILE*)file);
}
int seek(void* file, size_t pos, int whence) {
	return fseek((FILE*)file, pos, whence);
	
}
int tell(void* file) {
	return ftell((FILE*)file);
}