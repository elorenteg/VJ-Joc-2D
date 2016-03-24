#pragma once

#include "cScene.h"
#include "cSkyLayer.h"
#include "cMountainLayer.h"
#include "cPlayer.h"
#include "cData.h"
#include "cFont.h"
#include "cEnemyVertical.h"
#include "cEnemyHorizontal.h"
#include "cEnemyCircle.h"
#include "Globals.h"

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();
	bool InitEnemies(int level);

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);

	//Process
	bool Process();
	bool isEndOfGame();

	//Output
	void Render();
	void RenderMessage();
	void UpdateCameraScene();
	void RestartCameraScene();

private:
	unsigned char keys[256];
	cSkyLayer SkyLayer;
	cMountainLayer MountainLayer;
	cScene Scene;
	cPlayer Player;
	cData Data;
	cFont Font;
	vector<cEnemyVertical> EnemiesV;
	vector<cEnemyHorizontal> EnemiesH;
	vector<cEnemyCircle> EnemiesC;
	
	float cameraXScene;
	bool isGameOver;

	//http://www.koonsolo.com/news/dewitters-gameloop/
	const int FRAMES_PER_SECOND = 70;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	// Returns the current number of ms elapsed since the system was started
	DWORD next_game_tick = GetTickCount();
	int sleep_time = 0;
	bool game_is_running = true;
};
