#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "glm.hpp"

enum primitive_type {
	circle,
	cube,
	triangle
};

struct primitive {
	primitive_type type;
	glm::vec3 line;
	glm::vec3 fill;

	primitive() = default;

	//krug
	float radius;

	static primitive create_circle(const glm::vec3& line_color, const glm::vec3& fill_color, float r) {
		primitive p;
		p.type = primitive_type::circle;
		p.line = line_color;
		p.fill = fill_color;
		p.radius = r;
		return p;
	}

	//kocka
	float size;

	static primitive create_cube(const glm::vec3& line_color, const glm::vec3& fill_color, float s) {
		primitive p;
		p.type = primitive_type::cube;
		p.line = line_color;
		p.fill = fill_color;
		p.size = s;
		return p;
	}

	//trougao
	float base;
	float height;

	static primitive create_triangle(const glm::vec3& line_color, const glm::vec3& fill_color, float b, float h) {
		primitive p;
		p.type = primitive_type::triangle;
		p.line = line_color;
		p.fill = fill_color;
		p.base = b;
		p.height = h;
		return p;
	}
};
#endif #PRIMITIVE_H