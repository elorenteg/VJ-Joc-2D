#pragma once

#include "cTexture.h"
#include "Globals.h"

#define DEPTH			-9
#define SPEED			0.0005f

class cSkyLayer {
public:
	cSkyLayer(void);
	virtual ~cSkyLayer(void);

	void Draw(int tex_id);
	void endOfGame();

private:
	float texX = 0.0f;
	bool isEndOfGame;
};
