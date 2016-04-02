#pragma once

#include "cScene.h"
#include "cSkyLayer.h"
#include "cMountainLayer.h"
#include "cGameInfoLayer.h"
#include "cPlayer.h"
#include "cData.h"
#include "cFont.h"
#include "cEnemyVertical.h"
#include "cEnemyHorizontal.h"
#include "cEnemyCircle.h"
#include "Globals.h"

#define TOTAL_LEVELS	2

#define END_GAME_OVER	0
#define END_OF_GAME		1
#define END_OF_LEVEL	2
#define LIFE_LOST		3
#define GAME_PAUSED		4

#define GAME_OVER_MESSAGE			"GAME OVER"
#define END_OF_GAME_MESSAGE			"FI DEL JOC"
#define END_OF_LEVEL_MESSAGE		"FI DEL NIVELL"
#define END_OF_LEVEL_MESSAGE_NEXT	"PREM ENTER PER A PASSAR DE NIVELL"
#define GAME_PAUSED_MESSAGE			"PAUSA"
#define GAME_PAUSED_MESSAGE_NEXT	"PREM P PER A CONTINUAR JUGANT"
#define PLAYER_LOSES_LIFE_MESSAGE	"OH! VIDA PERDUDA"
#define PLAYER_LOSES_LIFE_MESSAGE_NEXT	"PREM ENTER PER A CONTINUAR JUGANT"

#define END_SCORE_MESSAGE			"PUNTUACIO"
#define END_LIFE_REM_MESSAGE		"VIDES REST"
#define END_TOTAL_SCORE_MESSAGE		"PUNT TOTAL"

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

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
	void RenderMessage(int message);
	void UpdateCameraScene();
	void RestartCameraScene();

	bool hasGameEnd();

private:
	unsigned char keys[256];
	cSkyLayer SkyLayer;
	cMountainLayer MountainLayer;
	cGameInfoLayer GameInfoLayer;
	cScene Scene;
	cPlayer Player;
	cData Data;
	cFont Font;
	vector<cEnemyVertical> EnemiesV;
	vector<cEnemyHorizontal> EnemiesH;
	vector<cEnemyCircle> EnemiesC;
	
	float cameraXScene;
	int currentLevel;
	bool gamePaused;
	bool gameEnd;

	//http://www.koonsolo.com/news/dewitters-gameloop/
	const int FRAMES_PER_SECOND = 70;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	// Returns the current number of ms elapsed since the system was started
	DWORD next_game_tick = GetTickCount();
	int sleep_time = 0;
	bool game_is_running = true;

	bool loadLevel(int level);
	bool initEnemies(int level);

	void startGame();
	bool isGameStandBy();
	bool isEndOfLevel();
	bool isPlayerOutsideWindow();
	bool isPlayerDead();
	bool isGamePaused();
};
