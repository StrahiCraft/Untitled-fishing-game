#pragma once
#include "Sprite.h"
#include <vector>

using namespace std;

class TextRenderer
{
private:
	glm::vec2 _textPosition;
	Sprite* _fontSheet;
	int _characterOffset;
	int _firstCharacterASCIIOffset;
	vector<Sprite*> _characterSprites;
public:
	TextRenderer(glm::vec2 textPosition, Sprite* fontSheet, int characterDistance, int firstCharacterASCIIOffset);
	void setText(string newText);
	void render();
};

