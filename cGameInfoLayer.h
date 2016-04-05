#pragma once

#include "cTexture.h"
#include "cData.h"
#include "cDataManager.h"
#include "cFont.h"
#include "Globals.h"

#define ABR_LEVEL_TEXT			"NIVELL"
#define ABR_HEALTH_TEXT			"VIDES"
#define ABR_SCORE_TEXT			"PUNTUACIO"
#define ABR_HIGH_SCORE_TEXT		"MAX PUNT"
#define ABR_HEALTH_BOSS_TEXT	"VIDA BOSS"

class cGameInfoLayer {
public:
	cGameInfoLayer(void);
	virtual ~cGameInfoLayer(void);

	bool Init();
	void Draw();

	void SetCurrentLevel(int level);
	int GetCurrentLevel();
	void SetHighScore(int score);
	int GetHighScore();
	void SetCurrentScore(int score);
	int GetCurrentScore();
	void SetCurrentLife(int life);
	int GetCurrentLife();
	void SetCurrentLifeBoss(int life);
	int GetCurrentLifeBoss();
	void SetShowBossLife(bool show);

	void SaveHighScore(int high_score);

private:
	cFont Font;
	cData Data;
	cDataManager DataManager;

	int current_level;
	int high_score;
	int current_score;
	int current_life;
	int current_life_boss;
	bool showBossLife;

	void drawImage(int tex_id, float x, float y, float z, float w, float h);
	void drawRectangle(float x, float y, float z, float width, float height);
};
