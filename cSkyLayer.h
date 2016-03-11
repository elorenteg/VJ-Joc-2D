#pragma once

#include "cTexture.h"
#include "Globals.h"

#define DEPTH			-10
#define SPEED			1

class cSkyLayer {
public:
	cSkyLayer(void);
	virtual ~cSkyLayer(void);

	void Draw(int tex_id);

private:
	float texX = 0.0f;
};
