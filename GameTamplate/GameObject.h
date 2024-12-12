#pragma once
#include "Sprite.h"
#include "Primitives.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

class GameObject {
private:
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

	primitive primitive;
	Sprite* sprite;

	glm::vec2 velocity;

	GLboolean is_visible;
	GLboolean is_active;
public:
	GameObject()
		: position(0.0f, 0.0f), velocity(0.0f, 0.0f),
		rotation(0.0f), scale(1.0f, 1.0f), primitive(), sprite(), is_visible(true), is_active(true) {}

	GameObject(const glm::vec2& pos, const glm::vec2& vel, const struct primitive& prim)
		: position(pos), velocity(vel), rotation(0.0f), scale(1.0f, 1.0f),
		primitive(prim), sprite(), is_visible(true), is_active(true) {}

	GameObject(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr)
		: position(pos), velocity(vel), rotation(0.0f), scale(1.0f, 1.0f),
		sprite(spr), is_visible(true), is_active(true) {}

	~GameObject() {
		delete sprite;
	}

	glm::vec2 get_position() const { return position; }
	void set_position(const glm::vec2& new_position) { position = new_position; }

	glm::vec2 get_velocity() const { return velocity; }
	void set_velocity(const glm::vec2& new_velocity) { velocity = new_velocity; }

	glm::vec3 get_line() const { return primitive.line; }
	void set_line(const glm::vec3& new_line) { primitive.line = new_line; }

	glm::vec3 get_fill() const { return primitive.fill; }
	void set_fill(const glm::vec3& new_fill) { primitive.fill = new_fill; }

	float get_rotation() const { return rotation; }
	void set_rotation(float new_rotation) { rotation = new_rotation; }

	glm::vec2 get_scale() const { return scale; }
	void set_scale(const glm::vec2& new_scale) { scale = new_scale; }

	Sprite* get_sprite() const { return sprite; }
	void set_sprite(Sprite* spr) { sprite = spr; }

	primitive_type get_primitive_type() const { return primitive.type; }

	GLboolean get_is_visible() const { return is_visible; }
	void set_is_visible(const GLboolean is_visible) { this->is_visible = is_visible; }

	GLboolean get_is_active() const { return is_active; }
	void set_is_active(const GLboolean is_active) { this->is_active = is_active; }

	void update(float dt) {
		if (is_active) {
			if (sprite) {
				sprite->update(dt);
			}
			position += velocity * dt;
			check_edges();
		}
	}

	void render() {
		glPushMatrix();

		glTranslatef(position.x, position.y, 0.0f);
		glRotatef(rotation, 0.0f, 0.0f, 1.0f);
		glScalef(scale.x, scale.y, 1.0f);

		if (is_visible) {
			if (sprite) {
				glEnable(GL_TEXTURE_2D);
				sprite->render();
				glDisable(GL_TEXTURE_2D);
			}

		switch (primitive.type) {
			case primitive_type::circle:
				draw_circle(primitive.radius);
				break;
			case primitive_type::cube:
				draw_cube(primitive.size);
				break;
			case primitive_type::triangle:
				draw_triangle(primitive.base, primitive.height);
				break;
			default:
				break;
			}
		}

		glPopMatrix();
	}

private:
	void draw_circle(float radius) {
		glDisable(GL_TEXTURE_2D);

		glLineWidth(2.0f);
		glColor3f(primitive.line.r, primitive.line.g, primitive.line.b);
		glBegin(GL_LINE_LOOP);
		const int segments = 50;
		for (int i = 0; i < segments; i++) {
			float theta = glm::radians((i / static_cast<float>(segments)) * 360.0f);
			glVertex2f(cos(theta) * radius, sin(theta) * radius);
		}
		glEnd();

		glColor3f(primitive.fill.r, primitive.fill.g, primitive.fill.b);
		glBegin(GL_POLYGON);
		for (int i = 0; i < segments; i++) {
			float theta = glm::radians((i / static_cast<float>(segments)) * 360.0f);
			glVertex2f(cos(theta) * radius, sin(theta) * radius);
		}
		glEnd();

		glEnable(GL_TEXTURE_2D);
	}

	void draw_cube(float size) {
		glDisable(GL_TEXTURE_2D);

		glLineWidth(2.0f);
		glColor3f(primitive.line.r, primitive.line.g, primitive.line.b);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-size / 2, -size / 2);
		glVertex2f(size / 2, -size / 2);
		glVertex2f(size / 2, size / 2);
		glVertex2f(-size / 2, size / 2);
		glEnd();

		glColor3f(primitive.fill.r, primitive.fill.g, primitive.fill.b);
		glBegin(GL_POLYGON);
		glVertex2f(-size / 2, -size / 2);
		glVertex2f(size / 2, -size / 2);
		glVertex2f(size / 2, size / 2);
		glVertex2f(-size / 2, size / 2);
		glEnd();

		glEnable(GL_TEXTURE_2D);
	}

	void draw_triangle(float base, float height) {
		glDisable(GL_TEXTURE_2D);

		glLineWidth(2.0f);
		glColor3f(primitive.line.r, primitive.line.g, primitive.line.b);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-base / 2, -height / 2);
		glVertex2f(base / 2, -height / 2);
		glVertex2f(0.0f, height / 2);
		glEnd();

		glColor3f(primitive.fill.r, primitive.fill.g, primitive.fill.b);
		glBegin(GL_POLYGON);
		glVertex2f(-base / 2, -height / 2);
		glVertex2f(base / 2, -height / 2);
		glVertex2f(0.0f, height / 2);
		glEnd();

		glEnable(GL_TEXTURE_2D);
	}

	void check_edges() {
		if (position.x > glutGet(GLUT_WINDOW_WIDTH)) {
			position.x = static_cast<float>(glutGet(GLUT_WINDOW_WIDTH));
		}
		else if (position.x < 0) {
			position.x = 0.0f;
		}
		if (position.y > glutGet(GLUT_WINDOW_HEIGHT)) {
			position.y = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT));
		}
		else if (position.y < 0) {
			position.y = 0.0f;
		}
	}
};
