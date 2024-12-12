#ifndef SPRITE_H
#define SPRITE_H

#include "SOIL2.h"
#include "glut.h"
#include "glm.hpp"

#include <iostream>

class Sprite {
private:
	GLuint* textures;
	unsigned int texture_index;
	unsigned int current_frame;
	unsigned int number_of_textures;
	glm::vec2 number_of_frames;

	GLfloat animation_delay;
	GLfloat animation_elapsed_time;

	GLboolean is_transparent;
	GLboolean is_sprite_sheet;

	glm::vec2 sprite_flip;
	glm::vec2 size;

public:
	Sprite() = default;
	Sprite(const char* file_name,
		glm::vec2 size,
		GLuint number_of_textures = 1,
		glm::vec2 number_of_frames = glm::vec2(1),
		GLboolean is_transparent = true) : size(size), number_of_frames(number_of_frames),
		animation_delay(0.25f), animation_elapsed_time(0.0f),
		is_transparent(is_transparent), sprite_flip(false) {

		this->number_of_textures = static_cast<unsigned int>(number_of_frames.x * number_of_frames.y);
		textures = new GLuint[this->number_of_textures];

		texture_index = 0;
		current_frame = 0;

		if (!add_texture(file_name, is_transparent))
			std::cout << "Texture loading failed: " << SOIL_last_result() << std::endl;
	}

	const bool add_texture(const char* file_name, const bool use_transparency) {
		GLuint texture = SOIL_load_OGL_texture(file_name, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

		if (texture == 0)
			return false;

		textures[texture_index] = texture;
		texture_index++;

		is_sprite_sheet = (texture_index == 1 && number_of_textures > 1);

		this->is_transparent = use_transparency;

		return true;
	}

	void update(GLfloat delta_time) {
		animation_elapsed_time += delta_time;
		if (animation_elapsed_time >= animation_delay) {
			current_frame++;
			if (current_frame >= number_of_textures)
				current_frame = 0;
			animation_elapsed_time = 0.0f;
		}
	}

	void render() {
		if (is_transparent) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glColor3f(1.0f, 1.0f, 1.0f);

		GLfloat x = 0;
		GLfloat y = 0;

		GLfloat w = size.x;
		GLfloat h = size.y;

		GLfloat texture_width = (GLfloat)texture_index / number_of_frames.x;
		GLfloat texture_height = (GLfloat)texture_index / number_of_frames.y;

		if (!is_sprite_sheet)
			texture_height = 1;

		GLfloat u = 0.0f;
		GLfloat v = 0.0f;

		if (texture_index < number_of_frames.x * number_of_frames.y) {
			GLuint current_y = current_frame / number_of_frames.x;
			GLuint current_x = current_frame - current_y * number_of_frames.x;

			u = static_cast<GLfloat>(current_x) * texture_width;
			v = static_cast<GLfloat>(current_y) * texture_height;
		}

		glBegin(GL_QUADS);

		// Default
		if (!sprite_flip.y && !sprite_flip.x) {
			glTexCoord2f(u, v + texture_height);					glVertex2f(x, y);
			glTexCoord2f(u + texture_width, v + texture_height);	glVertex2f(x + w, y);
			glTexCoord2f(u + texture_width, v);						glVertex2f(x + w, y + h);
			glTexCoord2f(u, v);										glVertex2f(x, y + h);
		}
		// Horizontal flip
		if (sprite_flip.y && !sprite_flip.x) {
			glTexCoord2f(u, v);										glVertex2f(x, y);
			glTexCoord2f(u + texture_width, v);						glVertex2f(x + w, y);
			glTexCoord2f(u + texture_width, v + texture_height);	glVertex2f(x + w, y + h);
			glTexCoord2f(u, v + texture_height);					glVertex2f(x, y + h);
		}
		// Vertical flip
		if (!sprite_flip.y && sprite_flip.x) {
			glTexCoord2f(u + texture_width, v + texture_height);	glVertex2f(x, y);
			glTexCoord2f(u, v + texture_height);					glVertex2f(x + w, y);
			glTexCoord2f(u, v);										glVertex2f(x + w, y + h);
			glTexCoord2f(u + texture_width, v);						glVertex2f(x, y + h);
		}
		// Horizontal && Vertical flip
		if (sprite_flip.y && sprite_flip.x) {
			glTexCoord2f(u + texture_width, v);						glVertex2f(x, y);
			glTexCoord2f(u, v);										glVertex2f(x + w, y);
			glTexCoord2f(u, v + texture_height);					glVertex2f(x + w, y + h);
			glTexCoord2f(u + texture_width, v + texture_height);	glVertex2f(x, y + h);
		}

		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);

		if (is_transparent) {
			glDisable(GL_BLEND);
		}
	}

	GLuint* get_textures() const { return textures; }
	void set_textures(const GLuint* textures) {
		if (textures == nullptr) {
			std::cerr << "Error: set_textures received a null pointer." << std::endl;
			return;
		}

		for (unsigned int i = 0; i < number_of_textures; ++i) {
			this->textures[i] = textures[i];
		}
	}

	unsigned int get_texture_index() const { return texture_index; }
	void set_texture_index(const unsigned int& texture_index) { this->texture_index = texture_index; }

	unsigned int get_current_frame() const { return current_frame; }
	void set_current_frame(const unsigned int& current_frame) { this->current_frame = current_frame; }

	unsigned int get_number_of_textures() const { return number_of_textures; }
	void set_number_of_textures(const unsigned int& number_of_textures) { this->number_of_textures = number_of_textures; }

	glm::vec2 get_number_of_frames() const { return number_of_frames; }
	void set_number_of_frames(const glm::vec2& number_of_frames) { this->number_of_frames = number_of_frames; }

	GLfloat get_animation_delay() const { return animation_delay; }
	void set_animation_delay(const GLfloat& animation_delay) { this->animation_delay = animation_delay; }

	GLfloat get_animation_elapsed_time() const { return animation_elapsed_time; }
	void set_animation_elapsed_time(const GLfloat& animation_elapsed_time) { this->animation_elapsed_time = animation_elapsed_time; }

	GLboolean get_is_transparent() const { return is_transparent; }
	void set_is_transparent(const GLboolean& is_transparent) { this->is_transparent = is_transparent; }

	GLboolean get_is_sprite_sheet() const { return is_sprite_sheet; }
	void set_is_sprite_sheet(const GLboolean& is_sprite_sheet) { this->is_sprite_sheet = is_sprite_sheet; }

	glm::vec2 get_sprite_flip() const { return sprite_flip; }
	void set_sprite_flip(const glm::vec2& sprite_flip) { this->sprite_flip = sprite_flip; }

	glm::vec2 get_size() const { return size; }
	void set_size(const glm::vec2& size) { this->size = size; }
};

#endif #SPRITE_H