#pragma once

#include "cTexture.h"
#include "Globals.h"
#include <windows.h>

#define SCENE_WIDTH		90
#define SCENE_HEIGHT	23

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		20

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);

	Matrix GetMap();
	void SetMap(Matrix &map);

	bool endOfMap(float cameraX);

	bool isEnemy(int tile_x, int tile_y);
	bool isScene(int tile_x, int tile_y);
	bool isBoss(int tile_x, int tile_y);
	void SetMapValue(int tile_x, int tile_y, int width, int heihgt, int value);

private:
	Matrix map;
	int id_DL;								//actual level display list
};
