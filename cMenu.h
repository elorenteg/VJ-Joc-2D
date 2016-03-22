#pragma once

#include "cData.h"
#include "cFont.h"
#include "Globals.h"

#define MENU		0
#define GAME		1
#define OPTIONS		2

#define PLAY_TEXT		"JUGAR"
#define OPTIONS_TEXT	"OPCIONS"
#define EXIT_TEXT		"SORTIR"

class cMenu
{
public:
	cMenu(void);
	virtual ~cMenu(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);

	//Process
	bool Process();

	//Output
	void Render();

	//State in use
	int GetState();

private:
	unsigned char keys[256];
	cData Data;
	cFont Font;
	bool processingKey;

	//http://www.koonsolo.com/news/dewitters-gameloop/
	const int FRAMES_PER_SECOND = 70;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	// Returns the current number of ms elapsed since the system was started
	DWORD next_game_tick = GetTickCount();
	int sleep_time = 0;
	bool game_is_running = true;

	enum Action { gameAction, optionsAction, stopAction };
	Action actionSelected;

	int currentState;

	void moveAction(int moveTo);
	void executeAction();
	void drawRectangle(float x, float y, float z, float width, float height);
};
