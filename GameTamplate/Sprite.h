#ifndef SPRITE_H
#define SPRITE_H

#include "SOIL2.h"
#include "glut.h"
#include "glm.hpp"

#include <iostream>

class Sprite {
private:
	GLuint* _textures;
	unsigned int _textureIndex;
	unsigned int _currentFrame;
	unsigned int _numberOfTextures;
	glm::vec2 _numberOfFrames;

	GLfloat _animationDelay;
	GLfloat _animationElapsedTime;

	GLboolean _isTransparent;
	GLboolean _isSpriteSheet;
	GLboolean _isAnimated = true;

	glm::vec2 _spriteFlip;
	glm::vec2 size;

public:
	Sprite() = default;
	Sprite(const char* fileName,
		glm::vec2 size,
		GLuint number_of_textures = 1,
		glm::vec2 numberOfFrames = glm::vec2(1),
		GLboolean isTransparent = true) : size(size), _numberOfFrames(numberOfFrames),
		_animationDelay(0.25f), _animationElapsedTime(0.0f),
		_isTransparent(isTransparent), _spriteFlip(false) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		this->_numberOfTextures = static_cast<unsigned int>(numberOfFrames.x * numberOfFrames.y);
		_textures = new GLuint[this->_numberOfTextures];

		_textureIndex = 0;
		_currentFrame = 0;

		if (!addTexture(fileName, isTransparent))
			std::cout << "Texture loading failed: " << SOIL_last_result() << std::endl;
	}

	const bool addTexture(const char* fileName, const bool useTransparency) {
		GLuint texture = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

		if (texture == 0)
			return false;

		_textures[_textureIndex] = texture;
		_textureIndex++;

		_isSpriteSheet = (_textureIndex == 1 && _numberOfTextures > 1);

		this->_isTransparent = useTransparency;

		return true;
	}

	void update(GLfloat deltaTime) {
		if (!_isAnimated) {
			return;
		}

		_animationElapsedTime += deltaTime;
		if (_animationElapsedTime >= _animationDelay) {
			_currentFrame++;
			if (_currentFrame >= _numberOfTextures)
				_currentFrame = 0;
			_animationElapsedTime = 0.0f;
		}
	}

	void render() {
		if (_isTransparent) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		glBindTexture(GL_TEXTURE_2D, _textures[0]);
		glColor3f(1.0f, 1.0f, 1.0f);

		GLfloat x = 0;
		GLfloat y = 0;

		GLfloat w = size.x;
		GLfloat h = size.y;

		GLfloat textureWidth = (GLfloat)_textureIndex / _numberOfFrames.x;
		GLfloat textureHeight = (GLfloat)_textureIndex / _numberOfFrames.y;

		if (!_isSpriteSheet)
			textureHeight = 1;

		GLfloat u = 0.0f;
		GLfloat v = 0.0f;

		if (_textureIndex < _numberOfFrames.x * _numberOfFrames.y) {
			GLuint currentY = _currentFrame / _numberOfFrames.x;
			GLuint currentX = _currentFrame - currentY * _numberOfFrames.x;

			u = static_cast<GLfloat>(currentX) * textureWidth;
			v = static_cast<GLfloat>(currentY) * textureHeight;
		}

		glBegin(GL_QUADS);

		// Default
		if (!_spriteFlip.y && !_spriteFlip.x) {
			glTexCoord2f(u, v + textureHeight);					glVertex2f(x, y);
			glTexCoord2f(u + textureWidth, v + textureHeight);	glVertex2f(x + w, y);
			glTexCoord2f(u + textureWidth, v);						glVertex2f(x + w, y + h);
			glTexCoord2f(u, v);										glVertex2f(x, y + h);
		}
		// Horizontal flip
		if (_spriteFlip.y && !_spriteFlip.x) {
			glTexCoord2f(u, v);										glVertex2f(x, y);
			glTexCoord2f(u + textureWidth, v);						glVertex2f(x + w, y);
			glTexCoord2f(u + textureWidth, v + textureHeight);	glVertex2f(x + w, y + h);
			glTexCoord2f(u, v + textureHeight);					glVertex2f(x, y + h);
		}
		// Vertical flip
		if (!_spriteFlip.y && _spriteFlip.x) {
			glTexCoord2f(u + textureWidth, v + textureHeight);	glVertex2f(x, y);
			glTexCoord2f(u, v + textureHeight);					glVertex2f(x + w, y);
			glTexCoord2f(u, v);										glVertex2f(x + w, y + h);
			glTexCoord2f(u + textureWidth, v);						glVertex2f(x, y + h);
		}
		// Horizontal && Vertical flip
		if (_spriteFlip.y && _spriteFlip.x) {
			glTexCoord2f(u + textureWidth, v);						glVertex2f(x, y);
			glTexCoord2f(u, v);										glVertex2f(x + w, y);
			glTexCoord2f(u, v + textureHeight);					glVertex2f(x + w, y + h);
			glTexCoord2f(u + textureWidth, v + textureHeight);	glVertex2f(x, y + h);
		}

		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);

		if (_isTransparent) {
			glDisable(GL_BLEND);
		}
	}

	GLuint* get_textures() const { return _textures; }
	void set_textures(const GLuint* textures) {
		if (textures == nullptr) {
			std::cerr << "Error: set_textures received a null pointer." << std::endl;
			return;
		}

		for (unsigned int i = 0; i < _numberOfTextures; ++i) {
			this->_textures[i] = textures[i];
		}
	}

	void setIsAnimated(const bool& isAnimated) { this->_isAnimated = isAnimated; }

	unsigned int getTextureIndex() const { return _textureIndex; }
	void setTextureIndex(const unsigned int& textureIndex) { this->_textureIndex = textureIndex; }

	unsigned int getCurrentFrame() const { return _currentFrame; }
	void setCurrentFrame(const unsigned int& currentFrame) { this->_currentFrame = currentFrame; }

	unsigned int getNumberOfTextures() const { return _numberOfTextures; }
	void setNumberOfTextures(const unsigned int& numberOfTextures) { this->_numberOfTextures = numberOfTextures; }

	glm::vec2 getNumberOfFrames() const { return _numberOfFrames; }
	void setNumberOfFrames(const glm::vec2& numberOfFrames) { this->_numberOfFrames = numberOfFrames; }

	GLfloat getAnimationDelay() const { return _animationDelay; }
	void setAnimationDelay(const GLfloat& animationDelay) { this->_animationDelay = animationDelay; }

	GLfloat getAnimationElapsedTime() const { return _animationElapsedTime; }
	void setAnimationElapsedTime(const GLfloat& animationElapsedTime) { this->_animationElapsedTime = animationElapsedTime; }

	GLboolean getIsTransparent() const { return _isTransparent; }
	void setIsTransparent(const GLboolean& isTransparent) { this->_isTransparent = isTransparent; }

	GLboolean getIsSpriteSheet() const { return _isSpriteSheet; }
	void setIsSpriteSheet(const GLboolean& isSpriteSheet) { this->_isSpriteSheet = isSpriteSheet; }

	glm::vec2 getSpriteFlip() const { return _spriteFlip; }
	void setSpriteFlip(const glm::vec2& spriteFlip) { this->_spriteFlip = spriteFlip; }

	glm::vec2 getSize() const { return size; }
	void setSize(const glm::vec2& size) { this->size = size; }
};

#endif #SPRITE_H