#include "Font.h"
#include "IO.h"
#include "Split.h"
#include "stdlib.h"
#include "Window.h"
#include "Texture2D.h"

Font::Font()
{

}

Font::Font(const char* fontName) {
	LoadFont(fontName);
}

void Font::LoadFont(const char* fontName) {
	string imageDestination = "Fonts/";
	imageDestination.append(fontName);
	imageDestination.append(".png");
	texture = _Texture2D::Create((char *)imageDestination.c_str());

	string resourcePath = "Fonts/";
	resourcePath.append(fontName);
	resourcePath.append(".fnt");
	
	void* file = NULL;
	int error;
	std::istream* stream = openStringStream(file, resourcePath.c_str(), error);
	string line;
	std::getline(*stream, line);
	int sizePos = line.find(" size") + 6;
	size = atoi(line.substr(sizePos, line.find(' ', sizePos)).c_str());
	std::getline(*stream, line);
	lineHeight = atoi(&line[18]);
	std::getline(*stream, line);
	std::getline(*stream, line);
	//now the line has "chars count=96"
	size_t amountOfCharacters = atoi(&line[12]);
	characters = vector<FontCharacter>(256);
	int j = 0;
	for (size_t i = 0; i < amountOfCharacters; i++)
	{
		j = 0;
		std::getline(*stream, line);
		//"id=54"3
		size_t id = atoi(&line[8]);
		characters[id].char_id = id;
		//"x=0"2
		characters[id].x = atoi(&line[18]);
		//"y=0"2
		characters[id].y = atoi(&line[25]);
		//"width=0"6
		characters[id].width = atoi(&line[36]);
		//"height=0"7
		characters[id].height = atoi(&line[48]);
		//"xoffset=0"8
		characters[id].xoffset = atoi(&line[61]);
		//"yoffset=0"8 
		characters[id].yoffset = atoi(&line[74]);
		//"xadvance=0"9 
		characters[id].xadvance = atoi(&line[88]);
		
	}

	closeStringStream(file);
}

FontCharacter Font::GetFontCharacter(char c) {
	return characters[c];
}

size_t Font::GetLineHeight() {
	return lineHeight;
}

size_t Font::GetSize()
{
	return size;
}

Font::~Font()
{
	_Texture2D::Delete(texture);
}
