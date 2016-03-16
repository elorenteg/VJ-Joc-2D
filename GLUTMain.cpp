
#include "Globals.h"
#include "cGame.h"
#include "cMenu.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

cGame Game;
cMenu Menu;

void AppRender()
{
	switch (Menu.GetState()) {
	case 0:
		Menu.Render();
		break;
	case 1:
		Game.Render();
		break;
	}
}

void AppKeyboard(unsigned char key, int x, int y)
{
	switch (Menu.GetState()) {
	case 0:
		Menu.ReadKeyboard(key, x, y, true);
		break;
	case 1:
		Game.ReadKeyboard(key, x, y, true);
		break;
	}
}

void AppKeyboardUp(unsigned char key, int x, int y)
{
	switch (Menu.GetState()) {
	case 0:
		Menu.ReadKeyboard(key, x, y, false);
		break;
	case 1:
		Game.ReadKeyboard(key, x, y, false);
		break;
	}
}

void AppSpecialKeys(int key, int x, int y)
{
	switch (Menu.GetState()) {
	case 0:
		Menu.ReadKeyboard(key, x, y, true);
		break;
	case 1:
		Game.ReadKeyboard(key, x, y, true);
		break;
	}
}

void AppSpecialKeysUp(int key, int x, int y)
{
	switch (Menu.GetState()) {
	case 0:
		Menu.ReadKeyboard(key, x, y, false);
		break;
	case 1:
		Game.ReadKeyboard(key, x, y, false);
		break;
	}
}

void AppMouse(int button, int state, int x, int y)
{
	switch (Menu.GetState()) {
	case 0:
		Menu.ReadMouse(button, state, x, y);
		break;
	case 1:
		Game.ReadMouse(button, state, x, y);
		break;
	}
}

void AppIdle()
{
	switch (Menu.GetState()) {
	case 0:
		if (!Menu.Loop()) exit(0);
		break;
	case 1:
		if (!Game.Loop()) exit(0);
		break;
	}
}

void main(int argc, char** argv)
{
	int res_x, res_y, pos_x, pos_y;

	//GLUT initialization
	glutInit(&argc, argv);

	//RGBA with double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	//Create centered window
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (res_x >> 1) - (GAME_WIDTH >> 1);
	pos_y = (res_y >> 1) - (GAME_HEIGHT >> 1);

	glutInitWindowPosition(pos_x, pos_y);
	glutInitWindowSize(GAME_WIDTH, GAME_HEIGHT);
	glutCreateWindow("Bubble returns!");

	/*glutGameModeString("800x600:32");
	glutEnterGameMode();*/

	//Make the default cursor disappear
	//glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutDisplayFunc(AppRender);
	glutKeyboardFunc(AppKeyboard);
	glutKeyboardUpFunc(AppKeyboardUp);
	glutSpecialFunc(AppSpecialKeys);
	glutSpecialUpFunc(AppSpecialKeysUp);
	glutMouseFunc(AppMouse);
	glutIdleFunc(AppIdle);

	Menu.Init();
	Game.Init();

	//Application loop
	glutMainLoop();
}
