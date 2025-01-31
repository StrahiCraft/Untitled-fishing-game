#include "TextRenderer.h"

TextRenderer::TextRenderer(glm::vec2 textPosition, Sprite* fontSheet, int characterDistance) {
	_textPosition = textPosition;
	_fontSheet = fontSheet;
	_characterOffset = characterDistance;
	_fontSheet->setIsAnimated(false);
}

void TextRenderer::setText(string newText) {
	_characterSprites.clear();

	for (int i = 0; i < newText.length(); i++) {
		_characterSprites.push_back(new Sprite(*_fontSheet));
		_characterSprites[i]->setCurrentFrame(newText[i] - 32);
	}
}

void TextRenderer::render() {
	glTranslatef(_textPosition.x, _textPosition.y, 0.0f);

	for (int i = 0; i < _characterSprites.size(); i++) {
		glTranslatef(_characterOffset, 0.0f, 0.0f);
		_characterSprites[i]->render();
	}

	glPopMatrix();
}
