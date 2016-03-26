#pragma once

#include "cData.h"
#include "cDataManager.h"
#include "cFont.h"
#include "cSound.h"
#include "Globals.h"

#define MENU		0
#define GAME		1
#define HOW_TO		2
#define CREDITS		3

#define PLAY_TEXT		"JUGAR"
#define HOW_TO_TEXT		"INSTRUCCIONS"
#define CREDITS_TEXT	"CREDITS"
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
	cDataManager DataManager;
	cSound Sound;
	bool processingKey;

	//http://www.koonsolo.com/news/dewitters-gameloop/
	const int FRAMES_PER_SECOND = 70;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	// Returns the current number of ms elapsed since the system was started
	DWORD next_game_tick = GetTickCount();
	int sleep_time = 0;
	bool game_is_running = true;

	enum Action { gameAction, howtoAction, creditsAction, stopAction };
	Action actionSelected;

	int internalState;
	int currentState;

	void moveAction(int moveTo);
	void executeAction();
	void drawRectangle(float x, float y, float z, float width, float height);

	int maxStars = 50;
	int time_same_stars = 5;
	vector<float> starsX;
	vector<float> starsY;

	void showMenu();
	void showInstrucctions();
	void showCredits();

	void calculate_stars();
};
