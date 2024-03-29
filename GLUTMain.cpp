#include "Globals.h"
#include "cGame.h"
#include "cMenu.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define MENUSTATE		1
#define GAMESTATE		2
#define GAMESTARTSTATE	3
cGame Game;
cMenu Menu;

int currentState;

void AppRender()
{
	switch (Menu.GetState()) {
	case MENU:
		Menu.Render();
		break;
	case GAME:
		if (!Game.HasGameEnd())
			Game.Render();
		else
			Menu.Render();
		break;
	}
}

void AppKeyboard(unsigned char key, int x, int y)
{
	switch (Menu.GetState()) {
	case MENU:
		Menu.ReadKeyboard(key, x, y, true);
		break;
	case GAME:
		Game.ReadKeyboard(key, x, y, true);
		break;
	}
}

void AppKeyboardUp(unsigned char key, int x, int y)
{
	switch (Menu.GetState()) {
	case MENU:
		Menu.ReadKeyboard(key, x, y, false);
		break;
	case GAME:
		Game.ReadKeyboard(key, x, y, false);
		break;
	}
}

void AppSpecialKeys(int key, int x, int y)
{
	switch (Menu.GetState()) {
	case MENU:
		Menu.ReadKeyboard(key, x, y, true);
		break;
	case GAME:
		Game.ReadKeyboard(key, x, y, true);
		break;
	}
}

void AppSpecialKeysUp(int key, int x, int y)
{
	switch (Menu.GetState()) {
	case MENU:
		Menu.ReadKeyboard(key, x, y, false);
		break;
	case GAME:
		Game.ReadKeyboard(key, x, y, false);
		break;
	}
}

void AppMouse(int button, int state, int x, int y)
{
	switch (Menu.GetState()) {
	case MENU:
		Menu.ReadMouse(button, state, x, y);
		break;
	case GAME:
		Game.ReadMouse(button, state, x, y);
		break;
	}
}

void AppIdle()
{
	switch (Menu.GetState()) {
	case MENU:
		currentState = MENUSTATE;
		if (!Menu.Loop()) exit(0);
		break;
	case START_GAME:
		if (currentState != START_GAME) {
			Game.reinitializeRenderCounter();
		}
		currentState = START_GAME;
		Game.SetGameEnd(false);
		Menu.SetState(GAME);
		break;
	case GAME:
		if (currentState != GAME) {
			Game.reinitializeRenderCounter();
		}
		currentState = GAME;
		bool res = Game.Loop();
		if (res && Game.HasGameEnd()) {
			Menu.SetState(MENU);
		}
		else if (!res) {
			exit(0);
		}
		break;
	}
}

void main(int argc, char** argv)
{
	int res_x, res_y, pos_x, pos_y;

	currentState = MENUSTATE;

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
	glutCreateWindow("Nyan Cat returns!");

	//glutGameModeString("800x600:32");
	//glutEnterGameMode();

	//Make the default cursor disappear
	glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutDisplayFunc(AppRender);
	glutKeyboardFunc(AppKeyboard);
	glutKeyboardUpFunc(AppKeyboardUp);
	glutSpecialFunc(AppSpecialKeys);
	glutSpecialUpFunc(AppSpecialKeysUp);
	//glutMouseFunc(AppMouse);
	glutIdleFunc(AppIdle);

	Menu.Init();
	Game.Init();

	//Application loop
	glutMainLoop();
}
