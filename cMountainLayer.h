#pragma once

#include "cTexture.h"
#include "Globals.h"

#define DEPTH			-5
#define SPEED			2

class cMountainLayer {
public:
	cMountainLayer(void);
	virtual ~cMountainLayer(void);

	void Draw(int tex_id);

private:
	int id_DL;								//actual level display list
	float texX = 0.0f;
};
