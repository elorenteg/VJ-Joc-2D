#pragma once

#include "cData.h"
#include "cDataManager.h"
#include "cFont.h"
#include "cSound.h"
#include "Globals.h"

#define MENU		0
#define START_GAME	1
#define GAME		2
#define HOW_TO		3
#define OPTIONS		4
#define CREDITS		5

#define APP_GAME_TEXT	"NYAN CAT RETURNS!"
#define PLAY_TEXT		"JUGAR"
#define HOW_TO_TEXT		"INSTRUCCIONS"
#define OPTIONS_TEXT	"OPCIONS"
#define CREDITS_TEXT	"CREDITS"
#define EXIT_TEXT		"SORTIR"

#define MAX_PAGES	3
#define PAGE_1		1
#define PAGE_2		2
#define PAGE_3		3

#define HOW_TO_PLAYER_TEXT_1_1 "PERSONATGES \\ JUGADOR"

#define HOW_TO_PLAYER_TEXT_1_2 "ENEMICS \\ MOREN AMB UN TRET"

#define HOW_TO_PLAYER_TEXT_2_1 "BOSSES \\ CALEN MOLTS TRETS"

#define HOW_TO_PLAYER_TEXT_3_1 "DISPARAR: ESPAI"
#define HOW_TO_PLAYER_TEXT_3_2 "PAUSA:    P    "
#define HOW_TO_PLAYER_TEXT_3_3 "MOVIMENT DEL JUGADOR:"

#define HOW_TO_DIVISION		"\\"

#define OPTIONS_HIGH_SCORE		"MAX. PUNTUACIO: "
#define OPTIONS_SELECCIO_PLAYER "SEL. PERSONATGE: "

#define CREDITS_MARC_TEXT	"MARC VILA GOMEZ"
#define CREDITS_ESTER_TEXT	"ESTER LORENTE GARCIA"
#define CREDITS_WHERE_TEXT	"VIDEOJOCS  FIB  UPC"
#define CREDITS_WHEN_TEXT	"QP 2015 2016"

#define EXIT_HOW_TEXT	"[ESC] SORTIR"

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
	void SetState(int state);
	int GetState();

private:
	unsigned char keys[256];
	cData Data;
	cFont Font;
	cDataManager DataManager;
	cSound Sound;
	bool processingKey;

	enum Action { gameAction, howtoAction, optionsAction, creditsAction, stopAction };
	Action actionSelected;

	int internalState;
	int currentState;
	int page;

	vector<int> playersIDArray;
	int currentPlayerIDPos;

	void moveAction(int moveTo);
	void executeAction();
	void drawRectangle(float x, float y, float z, float w, float h);
	void drawImage(int tex_id, float x, float y, float z, float w, float h);

	int maxStars = 50;
	int time_same_stars = 5;
	vector<float> starsX;
	vector<float> starsY;

	void showMenu();
	void showInstrucctions();
	void showOptions();
	void showCredits();

	void render_stars();
	void calculate_stars();

	void setPlayerSize();

	//http://www.koonsolo.com/news/dewitters-gameloop/
	const int FRAMES_PER_SECOND = 70;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	// Returns the current number of ms elapsed since the system was started
	DWORD next_game_tick;
	int sleep_time;
};
