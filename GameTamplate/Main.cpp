#include "MainMenu.h"
#include "Fishing.h"
#include "ReelingIn.h"
#include "FishCaught.h"
#include "GameOver.h"
#include "Intro.h"
#include "HighScore.h"

#include <time.h>

float _deltaTime;
int _previousTime;

int _windowWidth = 800;
int _windowHeight = 800;

Fish* _fish;
Player* _player;

float _playerSpeed = 500;

GameState* _currentState;

vector<string> _fishStats = {
	"FishStats/carp.fish",
	"FishStats/clownFish.fish",
	"FishStats/triggerClownFish.fish",
	"FishStats/tinCan.fish",
};

void changeGameState(GameState* newState);

void goToMainMenu() {
	changeGameState(new MainMenu(_player, _fish));
}

void goToHighScores() {
	changeGameState(new HighScore(_player, _fish));
}

void gameOver() {
	changeGameState(new GameOver(_player, _fish));
}

void togglePause() {
	_currentState->togglePause();
}

void quitGame() {
	exit(0);
}

void resetScore() {
	ScoreManager::setScore(0);
}

void burstStream() {
	ReelingIn* reelingIn = (ReelingIn*)_currentState;

	reelingIn->clearBombs();
}

void setupAudio() {
	AudioManager::init();
	AudioManager::addSong("fishing", "Audio/fishing.mp3");
	AudioManager::addSong("reelingIn", "Audio/reelingIn.mp3");
	AudioManager::addSound("fishCaught", "Audio/fishCaught.mp3");
	AudioManager::addSound("explode", "Audio/explode.mp3");
	AudioManager::addSound("ring", "Audio/ring.wav");
	AudioManager::addSound("chaosControl", "Audio/chaosControl.wav");
	AudioManager::addSound("BurstStream", "Audio/burstStream.wav");
}

void changeGameState(GameState* newState) {
	if (_currentState != NULL) {
		_currentState->onStateExit();
	}
	_currentState = newState;
	_currentState->onStateEnter();
}

void startFishing() {
	_fish->resetFish(_fishStats[rand() % _fishStats.size()]);
	changeGameState(new Fishing(_player, _fish, 1));
}

void onLineBreak() {
	ReelingIn* reelingIn = (ReelingIn*)_currentState;
	_fish->resetFish(_fishStats[rand() % _fishStats.size()]);
	changeGameState(new Fishing(_player, _fish, reelingIn->getLineStrength()));
}

void fishCaught() {
	changeGameState(new FishCaught(_player, _fish, new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true)));
}

void onClick() {
	_currentState->onClick(Input::getMouse().x, Input::getMouse().y);
}

void reelIn() {
	Fishing* fishing = (Fishing*)_currentState;
	changeGameState(new ReelingIn(_player, _fish, glm::vec2(_windowWidth, _windowHeight),
		fishing->getRemainigFishingTime() / 30.0f, fishing->getLineStrength(), 45, fishing->getStoneSprites()));
}

void setupEvents() {
	EventSystem::subscribeFunction("ReelIn", reelIn);
	EventSystem::subscribeFunction("StartFishing", startFishing);
	EventSystem::subscribeFunction("FishCaught", fishCaught);
	EventSystem::subscribeFunction("GameOver", gameOver);
	EventSystem::subscribeFunction("Reset", resetScore);
	EventSystem::subscribeFunction("Reset", startFishing);
	EventSystem::subscribeFunction("OnMouseClick", onClick);
	EventSystem::subscribeFunction("Quit", quitGame);
	EventSystem::subscribeFunction("Pause", togglePause);
	EventSystem::subscribeFunction("MainMenu", goToMainMenu);
	EventSystem::subscribeFunction("MainMenu", resetScore);
	EventSystem::subscribeFunction("HighScore", goToHighScores);
	EventSystem::subscribeFunction("BurstStream", burstStream);
	EventSystem::subscribeFunction("OnLineBreak", onLineBreak);
}

void initialize() {
	srand(time(NULL));
	glPointSize(10);
	glLineWidth(3);

	_fish = new Fish(glm::vec2(0), glm::vec2(0),
		new Sprite("Sprites/fish.png", glm::vec2(64, 32), 1, glm::vec2(1), true), glm::vec2(_windowWidth, _windowHeight));
	_fish->resetFish(_fishStats[rand() % _fishStats.size()]);

	_player = new Player(glm::vec2(400, 250), glm::vec2(0), 
		new Sprite("Sprites/hook.png", glm::vec2(32), 1, glm::vec2(1), true), _playerSpeed);

	setupEvents();
	setupAudio();
	ScoreManager::init();
	BackgroundManager::init();

	changeGameState(new Intro(_player, _fish));
}

void update() {
	_currentState->onStateUpdate();
}

void render() {
	//Cistimo sve piksele
	glClear(GL_COLOR_BUFFER_BIT);

	_currentState->render();

	//Menjamo bafer
	glutSwapBuffers();
}

void gameLoop(void) {
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	_deltaTime = (float)(currentTime - _previousTime) / 1000;
	_previousTime = currentTime;

	Time::updateTime(_deltaTime);

	update();
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

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_BORDERLESS | GLUT_CAPTIONLESS);
	glutInitWindowSize(_windowWidth, _windowHeight);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("CS232 Projekat");

	start();

	Input::setCallbackFunctions();
	initialize();

	glutDisplayFunc(gameLoop);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}