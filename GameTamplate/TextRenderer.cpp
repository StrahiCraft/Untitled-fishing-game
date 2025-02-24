#include "TextRenderer.h"

TextRenderer::TextRenderer(glm::vec2 textPosition, Sprite* fontSheet, int characterDistance, int firstCharacterASCIIOffset) {
	_textPosition = textPosition;
	_fontSheet = fontSheet;
	_characterOffset = characterDistance;
	_firstCharacterASCIIOffset = firstCharacterASCIIOffset;
	_fontSheet->setIsAnimated(false);
}

void TextRenderer::setText(string newText) {
	_characterSprites.clear();
	_text = newText;

	for (int i = 0; i < newText.length(); i++) {
		_characterSprites.push_back(new Sprite(*_fontSheet));
		_characterSprites[i]->setCurrentFrame(newText[i] - _firstCharacterASCIIOffset);
	}
}

void TextRenderer::render() {
	glPushMatrix();

	glTranslatef(_textPosition.x, _textPosition.y, 0.0f);

	int wordLetters = 1;

	for (int i = 0; i < _characterSprites.size(); i++) {
		glTranslatef(_characterOffset, 0, 0.0f);

		if (_text[i] == '_') {
			glTranslatef(wordLetters * -_characterOffset, -_characterOffset, 0.0f);
			wordLetters = 1;
		}
		else {
			_characterSprites[i]->render();
			wordLetters++;
		}
	}

	glPopMatrix();
}
