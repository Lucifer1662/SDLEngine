#pragma once
#include "Texture2D.h"
#include "FontCharacter.h"
#include <vector>

using std::vector;

class Font
{
	size_t lineHeight;
	size_t size;
	vector<FontCharacter> characters;

public:
	Texture2D* texture;
	FontCharacter GetFontCharacter(char c);
	size_t GetLineHeight();
	size_t GetSize();

	Font(const char* fontName);
	Font();
	~Font();

	void LoadFont(const char* fontName);
};

