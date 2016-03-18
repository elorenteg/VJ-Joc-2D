#pragma once

#include "cTexture.h"
#include "Globals.h"
#include <windows.h>

#define SCENE_WIDTH		45
#define SCENE_HEIGHT	28

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		16

#define DEPTH			0
#define SPEED			3

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);
	Matrix GetMap();

	bool endOfMap(float cameraX);

private:
	Matrix map;
	int id_DL;								//actual level display list
};
