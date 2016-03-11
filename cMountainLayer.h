#pragma once

#include "cTexture.h"
#include "Globals.h"

#define DEPTH			-5
#define SPEED			1.0f

class cMountainLayer {
public:
	cMountainLayer(void);
	virtual ~cMountainLayer(void);

	void Draw(int tex_id);
	void endOfGame();

private:
	float texX = 0.0f;
	bool isEndOfGame;
};
