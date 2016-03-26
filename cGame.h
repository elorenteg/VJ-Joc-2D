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

#define GAME_OVER_MESSAGE	 "GAME OVER"
#define END_OF_GAME_MESSAGE	 "END OF GAME"
#define END_OF_LEVEL_MESSAGE "END OF LEVEL"

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
	bool isGameOver;

	//http://www.koonsolo.com/news/dewitters-gameloop/
	const int FRAMES_PER_SECOND = 70;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	// Returns the current number of ms elapsed since the system was started
	DWORD next_game_tick = GetTickCount();
	int sleep_time = 0;
	bool game_is_running = true;

	bool loadLevel(int level);
	bool initEnemies(int level);

	bool isGameStandBy();
	bool isEndOfLevel();
	bool isPlayerDead();
};
