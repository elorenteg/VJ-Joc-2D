#include "cMenu.h"
#include "Globals.h"

cMenu::cMenu(void)
{
}

cMenu::~cMenu(void)
{
}

bool cMenu::Init()
{
	bool res = true;

	//Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	return res;
}

bool cMenu::Loop()
{
	bool res = true;

	res = Process();
	if (res) Render();

	next_game_tick += SKIP_TICKS;
	sleep_time = next_game_tick - GetTickCount();
	if (sleep_time >= 0) {
		Sleep(sleep_time);
	}
	else {
		// Shit, we are running behind!
	}

	return res;
}

void cMenu::Finalize()
{
}

//Input
void cMenu::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cMenu::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cMenu::Process()
{
	bool res = true;

	//Process Input
	if (keys[27])	res = false;

	/*if (keys[GLUT_KEY_UP])
		Player.Jump(Scene.GetMap());
	if (keys[GLUT_KEY_LEFT])
		Player.MoveLeft(Scene.GetMap());
	else if (keys[GLUT_KEY_RIGHT])
		Player.MoveRight(Scene.GetMap());
	else Player.Stop();*/

	//Game Logic
	//Player.Logic(Scene.GetMap());

	return res;
}

//Output
void cMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 1.0f, 0.0f);
	drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f + 25.0f, -1.0f, 300.0f, 75.0f);


	glColor3f(0.0f, 0.0f, 1.0f);
	drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f - 125.0f, -1.0f, 300.0f, 75.0f);

	glutSwapBuffers();
}

// Draw the rectangle
void cMenu::drawRectangle(float x, float y, float z, float width, float height) {
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x, y + height, z);
	glEnd();
}
