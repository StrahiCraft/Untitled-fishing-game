#pragma once
#include <glut.h>
#include <glm.hpp>
#include <vector>
#include <iostream>
#include "Time.h"

using namespace std;

static class BackgroundManager {
private:
	static vector<glm::vec3> _fullColorGradient;
	static glm::vec3 _topColor;
	static glm::vec3 _bottomColor;
	/// <summary>
	/// Value that represents the lerped distance between the top and bottom colors
	/// </summary>
	static float _distanceBetweenColors;
	static float _overlayTransparency;
public:
	static void init();
	static void setBackground(float lerpValue);
	static void render();
	static void renderOverlay();
private:
	static void setColor(float lerpValue, glm::vec3 &color);
};