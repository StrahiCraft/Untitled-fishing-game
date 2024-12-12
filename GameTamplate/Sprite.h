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

	glm::vec2 _spriteFlip;
	glm::vec2 size;

public:
	Sprite() = default;
	Sprite(const char* file_name,
		glm::vec2 size,
		GLuint number_of_textures = 1,
		glm::vec2 number_of_frames = glm::vec2(1),
		GLboolean is_transparent = true) : size(size), _numberOfFrames(number_of_frames),
		_animationDelay(0.25f), _animationElapsedTime(0.0f),
		_isTransparent(is_transparent), _spriteFlip(false) {

		this->_numberOfTextures = static_cast<unsigned int>(number_of_frames.x * number_of_frames.y);
		_textures = new GLuint[this->_numberOfTextures];

		_textureIndex = 0;
		_currentFrame = 0;

		if (!addTexture(file_name, is_transparent))
			std::cout << "Texture loading failed: " << SOIL_last_result() << std::endl;
	}

	const bool addTexture(const char* file_name, const bool use_transparency) {
		GLuint texture = SOIL_load_OGL_texture(file_name, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

		if (texture == 0)
			return false;

		_textures[_textureIndex] = texture;
		_textureIndex++;

		_isSpriteSheet = (_textureIndex == 1 && _numberOfTextures > 1);

		this->_isTransparent = use_transparency;

		return true;
	}

	void update(GLfloat delta_time) {
		_animationElapsedTime += delta_time;
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

	unsigned int getTextureIndex() const { return _textureIndex; }
	void setTextureIndex(const unsigned int& texture_index) { this->_textureIndex = texture_index; }

	unsigned int getCurrentFrame() const { return _currentFrame; }
	void setCurrentFrame(const unsigned int& current_frame) { this->_currentFrame = current_frame; }

	unsigned int getNumberOfTextures() const { return _numberOfTextures; }
	void setNumberOfTextures(const unsigned int& number_of_textures) { this->_numberOfTextures = number_of_textures; }

	glm::vec2 getNumberOfFrames() const { return _numberOfFrames; }
	void setNumberOfFrames(const glm::vec2& number_of_frames) { this->_numberOfFrames = number_of_frames; }

	GLfloat getAnimationDelay() const { return _animationDelay; }
	void setAnimationDelay(const GLfloat& animation_delay) { this->_animationDelay = animation_delay; }

	GLfloat getAnimationElapsedTime() const { return _animationElapsedTime; }
	void setAnimationElapsedTime(const GLfloat& animation_elapsed_time) { this->_animationElapsedTime = animation_elapsed_time; }

	GLboolean getIsTransparent() const { return _isTransparent; }
	void setIsTransparent(const GLboolean& is_transparent) { this->_isTransparent = is_transparent; }

	GLboolean getIsSpriteSheet() const { return _isSpriteSheet; }
	void setIsSpriteSheet(const GLboolean& is_sprite_sheet) { this->_isSpriteSheet = is_sprite_sheet; }

	glm::vec2 getSpriteFlip() const { return _spriteFlip; }
	void setSpriteFlip(const glm::vec2& sprite_flip) { this->_spriteFlip = sprite_flip; }

	glm::vec2 getSize() const { return size; }
	void setSize(const glm::vec2& size) { this->size = size; }
};

#endif #SPRITE_H