#include "GameObject.h"
#include "Input.h"

#include <vector>

float delta_time;
int previous_time;

int window_width = 800;
int window_height = 500;

GameObject* player;

void initialize() {
	player = new GameObject(
		glm::vec2(0.0f),
		glm::vec2(0.0f),
		new Sprite("Sprites/player.png", glm::vec2(26, 22), 1, glm::vec2(8, 1), (GLboolean)false)
	);
}

void update(float dt) {
	
	if (Input::get_key('A')) {
		float new_x = player->get_position().x;
		new_x -= 300.0f * dt;
		player->set_position(glm::vec2(new_x, player->get_position().y));
		player->get_sprite()->set_sprite_flip(glm::vec2(true, false));
	}
	if (Input::get_key('D')) {
		float new_x = player->get_position().x;
		new_x += 300.0f * dt;
		player->set_position(glm::vec2(new_x, player->get_position().y));
		player->get_sprite()->set_sprite_flip(glm::vec2(false, false));
	}

	player->update(dt);

	Input::update();
}

void render() {

	//Cistimo sve piksele
	glClear(GL_COLOR_BUFFER_BIT);

	player->render();

	//Menjamo bafer
	glutSwapBuffers();

}

void game_loop(void) {
	int current_time = glutGet(GLUT_ELAPSED_TIME);
	delta_time = (float)(current_time - previous_time) / 1000;
	previous_time = current_time;

	update(delta_time);
	render();

	glutPostRedisplay();

}

void init_game(void) {
	glClearColor(100.0 / 255.0, 100.0 / 255.0, 100.0 / 255.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void reshape(int w, int h) {
	window_width = w;
	window_height = h;

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
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Tamplate!");

	init_game();

	Input::set_callback_functions();
	initialize();

	glutDisplayFunc(game_loop);
	glutReshapeFunc(reshape);

	glutMainLoop();


	return 0;
}

