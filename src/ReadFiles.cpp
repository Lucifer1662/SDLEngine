#include <string>
#include "ReadFiles.h"
#include "IO.h"
#include <iostream>
class ifstream;

using std::cout;
using std::endl;
using std::string;

string ReadFile(string filePath) {
	void* file = NULL;
	int error;

	std::istream* ifs = openStringStream(file, filePath.c_str(), error);
	std::string str((std::istreambuf_iterator<char>(*ifs)), std::istreambuf_iterator<char>());
	close(file);
	return str;
}

void ReadFile(void* buffer, GLuint bytesize, GLuint length, string fileFullPath) {

	void* file = NULL;
	int error = open(file, fileFullPath.c_str());
	if (error != 0) {
		cout << "Failed to open file, error :" << error;
		return;
	}
	
	read((void*)buffer, bytesize, length, file);

	close(file);
}

