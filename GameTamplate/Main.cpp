#include "Input.h"
#include "Fishing.h"
#include "ReelingIn.h"
#include "EventSystem.h"

#include <time.h>

float _deltaTime;
int _previousTime;

int _windowWidth = 800;
int _windowHeight = 500;

Fish* fish;
Player* player;

float playerSpeed = 500;

GameState* currentState;

void changeGameState(GameState* newState) {
	currentState = newState;
	currentState->onStateEnter();
}

void reelIn() {
	changeGameState(new ReelingIn(player, fish));
}

void initialize() {
	srand(time(NULL));
	glPointSize(10);
	glLineWidth(3);

	fish = new Fish(glm::vec2(0), glm::vec2(0),
		new Sprite("Sprites/fish.png", glm::vec2(32), 1, glm::vec2(1), true), glm::vec2(_windowWidth, _windowHeight));

	player = new Player(glm::vec2(400, 250), glm::vec2(0), 
		new Sprite("Sprites/hook.png", glm::vec2(32), 1, glm::vec2(1), true), playerSpeed);

	changeGameState(new Fishing(player, fish));

	EventSystem::subscribeFunction("ReelIn", reelIn);
}

void update(float deltaTime) {
	currentState->onStateUpdate(deltaTime);
}

void render() {
	//Cistimo sve piksele
	glClear(GL_COLOR_BUFFER_BIT);

	fish->render();
	player->render();

	//Menjamo bafer
	glutSwapBuffers();
}

void gameLoop(void) {
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	_deltaTime = (float)(currentTime - _previousTime) / 1000;
	_previousTime = currentTime;

	update(_deltaTime);
	render();

	glutPostRedisplay();
}

void start(void) {
	glClearColor(0, 0, 0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void reshape(int w, int h) {
	_windowWidth = w;
	_windowHeight = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(_windowWidth, _windowHeight);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("CS232 Projekat");

	start();

	Input::setCallbackFunctions();
	initialize();

	glutDisplayFunc(gameLoop);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}

