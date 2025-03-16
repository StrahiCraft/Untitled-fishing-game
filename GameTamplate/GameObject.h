#pragma once
#include "Sprite.h"
#include "Primitives.h"
#include "Time.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

class GameObject {
protected:
	glm::vec2 _position;
	float _rotation;
	glm::vec2 _scale;

	primitive _primitive;
	Sprite* _sprite;

	glm::vec2 _velocity;

	GLboolean _visible;
	GLboolean _active;
public:
	GameObject()
		: _position(0.0f, 0.0f), _velocity(0.0f, 0.0f),
		_rotation(0.0f), _scale(1.0f, 1.0f), _primitive(), _sprite(), _visible(true), _active(true) {}

	GameObject(const glm::vec2& pos, const glm::vec2& vel, const struct primitive& prim)
		: _position(pos), _velocity(vel), _rotation(0.0f), _scale(1.0f, 1.0f),
		_primitive(prim), _sprite(), _visible(true), _active(true) {}

	GameObject(const glm::vec2& pos, const glm::vec2& vel, Sprite* spr)
		: _position(pos), _velocity(vel), _rotation(0.0f), _scale(1.0f, 1.0f),
		_sprite(spr), _visible(true), _active(true) {}

	~GameObject() {
		delete this;
	}

	glm::vec2 getPosition() const { return _position; }
	void setPosition(const glm::vec2& new_position) { _position = new_position; }

	glm::vec2 getVelocity() const { return _velocity; }
	void setVelocity(const glm::vec2& new_velocity) { _velocity = new_velocity; }

	glm::vec3 getLine() const { return _primitive.line; }
	void setLine(const glm::vec3& new_line) { _primitive.line = new_line; }

	glm::vec3 getFill() const { return _primitive.fill; }
	void setFill(const glm::vec3& new_fill) { _primitive.fill = new_fill; }

	float getRotation() const { return _rotation; }
	void setRotation(float new_rotation) { _rotation = new_rotation; }

	glm::vec2 getScale() const { return _scale; }
	void setScale(const glm::vec2& new_scale) { _scale = new_scale; }

	Sprite* getSprite() const { return _sprite; }
	void setSprite(Sprite* spr) { _sprite = spr; }

	primitiveType getPrimitiveType() const { return _primitive.type; }

	GLboolean getVisible() const { return _visible; }
	void setVisible(const GLboolean is_visible) { this->_visible = is_visible; }

	GLboolean getActive() const { return _active; }
	void setActive(const GLboolean is_active) { this->_active = is_active; }

	float getVelocityAngle();
	float getVelocityMagnitude();

	virtual void update() {
		if (_active) {
			if (_sprite) {
				_sprite->update(Time::getDeltaTime());
			}
			_position += _velocity * Time::getDeltaTime();
			checkEdges();
		}
	}

	virtual void render() {
		glPushMatrix();

		glTranslatef(_position.x, _position.y, 0.0f);
		glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
		glScalef(_scale.x, _scale.y, 1.0f);

		if (_visible) {
			if (_sprite) {
				glEnable(GL_TEXTURE_2D);
				_sprite->render();
				glDisable(GL_TEXTURE_2D);
			}

		switch (_primitive.type) {
			case primitiveType::circle:
				drawCircle(_primitive.radius);
				break;
			case primitiveType::cube:
				drawCube(_primitive.size);
				break;
			case primitiveType::triangle:
				drawTriangle(_primitive.base, _primitive.height);
				break;
			default:
				break;
			}
		}

		glPopMatrix();
	}

protected:
	void drawCircle(float radius) {
		glDisable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glLineWidth(2.0f);
		glColor3f(_primitive.line.r, _primitive.line.g, _primitive.line.b);
		glBegin(GL_LINE_LOOP);
		const int segments = 50;
		for (int i = 0; i < segments; i++) {
			float theta = glm::radians((i / static_cast<float>(segments)) * 360.0f);
			glVertex2f(cos(theta) * radius, sin(theta) * radius);
		}
		glEnd();

		glColor4f(_primitive.fill.r, _primitive.fill.g, _primitive.fill.b, 0.4f);
		glBegin(GL_POLYGON);
		for (int i = 0; i < segments; i++) {
			float theta = glm::radians((i / static_cast<float>(segments)) * 360.0f);
			glVertex2f(cos(theta) * radius, sin(theta) * radius);
		}
		glEnd();

		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
	}

	void drawCube(float size) {
		glDisable(GL_TEXTURE_2D);

		glLineWidth(2.0f);
		glColor3f(_primitive.line.r, _primitive.line.g, _primitive.line.b);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-size / 2, -size / 2);
		glVertex2f(size / 2, -size / 2);
		glVertex2f(size / 2, size / 2);
		glVertex2f(-size / 2, size / 2);
		glEnd();

		glColor3f(_primitive.fill.r, _primitive.fill.g, _primitive.fill.b);
		glBegin(GL_POLYGON);
		glVertex2f(-size / 2, -size / 2);
		glVertex2f(size / 2, -size / 2);
		glVertex2f(size / 2, size / 2);
		glVertex2f(-size / 2, size / 2);
		glEnd();

		glEnable(GL_TEXTURE_2D);
	}

	void drawTriangle(float base, float height) {
		glDisable(GL_TEXTURE_2D);

		glLineWidth(2.0f);
		glColor3f(_primitive.line.r, _primitive.line.g, _primitive.line.b);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-base / 2, -height / 2);
		glVertex2f(base / 2, -height / 2);
		glVertex2f(0.0f, height / 2);
		glEnd();

		glColor3f(_primitive.fill.r, _primitive.fill.g, _primitive.fill.b);
		glBegin(GL_POLYGON);
		glVertex2f(-base / 2, -height / 2);
		glVertex2f(base / 2, -height / 2);
		glVertex2f(0.0f, height / 2);
		glEnd();

		glEnable(GL_TEXTURE_2D);
	}

	void checkEdges() {
		if (_position.x > glutGet(GLUT_WINDOW_WIDTH) - 30) {
			_position.x = static_cast<float>(glutGet(GLUT_WINDOW_WIDTH) - 30);
		}
		else if (_position.x < 30) {
			_position.x = 30;
		}
		if (_position.y > glutGet(GLUT_WINDOW_HEIGHT) - 30) {
			_position.y = static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT) - 30);
		}
		else if (_position.y < 30) {
			_position.y = 30;
		}
	}
};