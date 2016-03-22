#include "cMenu.h"

cMenu::cMenu(void)
{
}

cMenu::~cMenu(void)
{
}

bool cMenu::Init()
{
	bool res = true;
	actionSelected = gameAction;
	processingKey = false;
	currentState = MENU;

	//Graphics initialization
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	char font_path[64];
	strcpy(font_path, IMAGES_FOLDER);
	strcat(font_path, "/");
	strcat(font_path, "font.png");
	res = Data.LoadImage(IMG_FONT, font_path, GL_RGBA);
	if (!res) return false;
	Font.setFont(Data.GetID(IMG_FONT), 256, 256, 19, 29);

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

	processingKey = press;
}

void cMenu::ReadMouse(int button, int state, int x, int y)
{

}

//Process
bool cMenu::Process()
{
	bool res = true;

	if (processingKey) {
		processingKey = false;

		//Process Input
		if (keys[27]) {
			res = false;
		}

		if (keys[GLUT_KEY_UP]) {
			moveAction(-1);
		}
		else if (keys[GLUT_KEY_DOWN]) {
			moveAction(1);
		}

		if (keys[13]) {
			executeAction();
		}
	}

	return res;
}

//Output
void cMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		Font.drawText(GAME_WIDTH / 2.0f - 105.0f, GAME_HEIGHT / 2.0f + 88.0f, 200.0f, 50.0f, PLAY_TEXT);

		glColor3f(1.0f, 1.0f, 1.0f);
		Font.drawText(GAME_WIDTH / 2.0f - 100.0f, GAME_HEIGHT / 2.0f - 12.0f, 200.0f, 50.0f, OPTIONS_TEXT);

		glColor3f(1.0f, 01.0f, 1.0f);
		Font.drawText(GAME_WIDTH / 2.0f - 105.0f, GAME_HEIGHT / 2.0f - 112.0f, 200.0f, 50.0f, EXIT_TEXT);
	glPopMatrix();
	
	glPushMatrix();
		if (actionSelected == gameAction)
			glColor3f(1.0f, 0.0f, 0.0f);
		else
			glColor3f(0.5f, 0.5f, 0.5f);
		drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f + 75.0f, -1.0f, 300.0f, 75.0f);

		if (actionSelected == optionsAction)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(0.5f, 0.5f, 0.5f);
		drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f - 25.0f, -1.0f, 300.0f, 75.0f);

	if (actionSelected == stopAction)
		glColor3f(0.0f, 0.0f, 1.0f);
	else
		glColor3f(0.5f, 0.5f, 0.5f);
	drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f - 125.0f, -1.0f, 300.0f, 75.0f);

	glutSwapBuffers();
}

//State in use
int cMenu::GetState() {
	return currentState;
}

void cMenu::executeAction() {
	if (actionSelected == gameAction) {
		currentState = GAME;
	}
	else if (actionSelected == optionsAction) {

	}
	else if (actionSelected == stopAction) {
		exit(0);
	}
}

void cMenu::moveAction(int moveTo) {
	if (actionSelected == gameAction) {
		if (moveTo == 1) {
			actionSelected = optionsAction;
		}
	}
	else if (actionSelected == optionsAction) {
		if (moveTo == 1) {
			actionSelected = stopAction;
		}
		else if (moveTo == -1) {
			actionSelected = gameAction;
		}
	}
	else if (actionSelected == stopAction) {
		if (moveTo == -1) {
			actionSelected = optionsAction;
		}
	}
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
