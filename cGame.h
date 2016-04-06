#pragma once

#include "cScene.h"
#include "cSkyLayer.h"
#include "cMountainLayer.h"
#include "cGameInfoLayer.h"
#include "cDataManager.h"
#include "cBicho.h"
#include "cPlayer.h"
#include "cData.h"
#include "cFont.h"
#include "cEnemyVertical.h"
#include "cEnemyHorizontal.h"
#include "cEnemyCircle.h"
#include "cBoss.h"
#include "cSound.h"
#include "Globals.h"

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
	void UpdateCameraScene();
	void RestartCameraScene();

	void SetGameEnd(bool end);
	bool HasGameEnd();

private:
	unsigned char keys[256];
	cSkyLayer SkyLayer;
	cMountainLayer MountainLayer;
	cGameInfoLayer GameInfoLayer;
	cScene Scene;
	cPlayer Player;
	cData Data;
	cFont Font;
	vector<cBicho*> Enemies;
	cBoss* Boss;
	cSound Sound;
	cDataManager DataManager;
	
	float cameraXScene;
	int currentLevel;
	bool gamePaused;
	bool gameEnd;
	bool playerLostLife;
	bool bossDead;
	int currentPlayerID;

	bool loadLevel(int level);
	bool initEnemies(int level);

	bool checkPlayerPosition();
	bool isPositionInsideX(float x, float y, float h, float xPlayer, float yPlayer, int wPlayer, int hPlayer);
	bool isPositionInsideY(float x, float y, float w, float xPlayer, float yPlayer, int wPlayer, int hPlayer);
	bool checkPlayerProjectiles();
	bool checkBossDead();
	bool checkEnemiesProjectiles();
	bool checkProjectilesEnemy(vector<Projectile>& projs);
	bool checkPositionWithEnemy(float enX, float enY, int enW, int enH);

	void startSound(int sound);
	void renderMessage(int message);

	void startGame();
	bool isGameStandBy();
	bool isEndOfLevel();
	bool isPlayerOutsideWindow();
	bool isPlayerDead();
	bool isGamePaused();
	bool isPlayerLostLife();
	bool isBossDead();
	bool isEndOfMap();
	bool isBossInScene();

	void setPlayerSize();

	//http://www.koonsolo.com/news/dewitters-gameloop/
	const int FRAMES_PER_SECOND = 70;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	// Returns the current number of ms elapsed since the system was started
	DWORD next_game_tick;
	int sleep_time;
};
