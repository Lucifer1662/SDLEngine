#pragma once
#include <sstream>
using std::stringstream;



std::istream* openStringStream(void*& file, const char * filePath, int& error);
int closeStringStream(void* file);

int open(void*& file, const char * filePath);
int read(void* buffer, size_t size, size_t length, void* file);
int close(void* file);
int seek(void* file, size_t pos, int whence);
int tell(void* file);
