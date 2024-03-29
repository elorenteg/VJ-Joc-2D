#pragma once

#include "cTexture.h"
#include "Globals.h"

#define DEPTH			-8
#define SPEED			0.001f

class cMountainLayer {
public:
	cMountainLayer(void);
	virtual ~cMountainLayer(void);

	void Draw(int tex_id, int level);
	void endOfLevel();
	void restartLevel();

private:
	float texX = 0.0f;
	bool isEndOfLevel;
};
