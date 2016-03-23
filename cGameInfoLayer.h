#pragma once

#include "cTexture.h"
#include "cData.h"
#include "cFont.h"
#include "Globals.h"

#define ABR_LEVEL_TEXT		"LVL"
#define ABR_HEALTH_TEXT		"VIDA"
#define ABR_SCORE_TEXT		"PUNT."
#define ABR_HIGH_SCORE_TEXT		"RECORD"

class cGameInfoLayer {
public:
	cGameInfoLayer(void);
	virtual ~cGameInfoLayer(void);

	bool Init();
	void Draw();

private:
	cFont Font;
	cData Data;

	int current_level;
	int high_score;
	int current_score;
	int current_life;
};
