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
	vector<Sprite*> _characterSprites;
public:
	TextRenderer(glm::vec2 textPosition, Sprite* fontSheet, int characterDistance);
	void setText(string newText);
	void render();
};

