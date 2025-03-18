#include "BackgroundManager.h"

vector<glm::vec3> BackgroundManager::_fullColorGradient;
glm::vec3 BackgroundManager::_topColor;
glm::vec3 BackgroundManager::_bottomColor;
float BackgroundManager::_distanceBetweenColors;

void BackgroundManager::init() {
	_distanceBetweenColors = 0.2f;

	_fullColorGradient.push_back(glm::vec3(9.0f / 255.0f, 4.0f / 255.0f, 87.0f / 255.0f));
	_fullColorGradient.push_back(glm::vec3(56.0f / 255.0f, 56.0f / 255.0f, 194.0f / 255.0f));
	_fullColorGradient.push_back(glm::vec3(0.0f / 255.0f, 212.0f / 255.0f, 255.0f / 255.0f));
	_fullColorGradient.push_back(glm::vec3(0.0f / 255.0f, 255.0f / 255.0f, 201.0f / 255.0f));

	_topColor = _fullColorGradient[_fullColorGradient.size() - 1];
	_bottomColor = _fullColorGradient[0];
} 

/// <summary>
/// Sets the colors of the background based on a custom lerp function
/// </summary>
/// <param name="lerpValue"> should be between 0 and 100</param>
void BackgroundManager::setBackground(float lerpValue) {
	setColor(lerpValue, _topColor);
	setColor(lerpValue - _distanceBetweenColors, _bottomColor);
}

void BackgroundManager::render() {
	glBegin(GL_QUADS);
	glColor3f(_topColor.r, _topColor.g, _topColor.b);
	glVertex2f(0, 800);
	glVertex2f(800, 800);
	glColor3f(_bottomColor.r, _bottomColor.g, _bottomColor.b);
	glVertex2f(800, 0);
	glVertex2f(0, 0);
	glEnd();
}

void BackgroundManager::renderOverlay() {
	glDisable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glBegin(GL_QUADS);
	glColor4f(_topColor.r, _topColor.g, _topColor.b, 0.3f);
	glVertex2f(0, 1000);
	glVertex2f(800, 1000);
	glColor4f(_bottomColor.r, _bottomColor.g, _bottomColor.b, 0.3f);
	glVertex2f(800, -200);
	glVertex2f(0, -200);
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
}

void BackgroundManager::setColor(float lerpValue, glm::vec3 &color) {
	if (lerpValue > 1) {
		lerpValue = 1;
	}
	else if (lerpValue < 0) {
		lerpValue = 0;
	}

	int colorIndex = round(lerpValue * _fullColorGradient.size() - 1);
	if (colorIndex <= 0) {
		colorIndex = 1;
	}
	lerpValue = lerpValue * _fullColorGradient.size() - colorIndex - 0.5f;
	color = glm::mix(_fullColorGradient[colorIndex - 1], _fullColorGradient[colorIndex], lerpValue);
}
