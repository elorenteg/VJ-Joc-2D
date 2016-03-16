#pragma once

#include "cData.h"
#include "Globals.h"

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

private:
	unsigned char keys[256];
	cData Data;
	bool processingKey;

	//http://www.koonsolo.com/news/dewitters-gameloop/
	const int FRAMES_PER_SECOND = 70;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	// Returns the current number of ms elapsed since the system was started
	DWORD next_game_tick = GetTickCount();
	int sleep_time = 0;
	bool game_is_running = true;

	enum Action { game, options, stop };
	Action actionSelected;

	void moveAction(int moveTo);
	void executeAction();
	void drawRectangle(float x, float y, float z, float width, float height);
};
