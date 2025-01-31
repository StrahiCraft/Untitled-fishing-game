#include "Fishing.h"
#include "ReelingIn.h"
#include "TextRenderer.h"

#include <time.h>

float _deltaTime;
int _previousTime;

int _windowWidth = 800;
int _windowHeight = 800;

Fish* fish;
Player* player;

float playerSpeed = 500;

GameState* currentState;

TextRenderer* scoreText;
int score = 0;

void resetScore() {
	score = 0;
	scoreText->setText("Score:" + to_string(score));
}

void changeGameState(GameState* newState) {
	currentState = newState;
	currentState->onStateEnter();
}

void startFishing() {
	changeGameState(new Fishing(player, fish));
	fish->resetFish();
	scoreText->setText("Score:" + to_string(++score));
}

void reelIn() {
	// TODO make reel in threshold depend on fish type
	changeGameState(new ReelingIn(player, fish, glm::vec2(_windowWidth, _windowHeight), 40, rand() % 25 + 10));
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
	EventSystem::subscribeFunction("StartFishing", startFishing);
	EventSystem::subscribeFunction("GameOver", startFishing);
	EventSystem::subscribeFunction("GameOver", resetScore);

	scoreText = new TextRenderer(glm::vec2(0, 750), 
		new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true), 27, 32);
	scoreText->setText("Score:" + to_string(score));
}

void update(float deltaTime) {
	currentState->onStateUpdate(deltaTime);
}

void render() {
	//Cistimo sve piksele
	glClear(GL_COLOR_BUFFER_BIT);

	currentState->render();
	scoreText->render();

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

