#pragma once

#include "cTexture.h"

#define SCENE_Xo		0
#define SCENE_Yo		0
#define SCENE_WIDTH		45
#define SCENE_HEIGHT	28

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		16
#define BLOCK_SIZE		24

#define DEPTH			0
#define SPEED			3

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);
	int *GetMap();

	bool endOfMap(float cameraX);

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int id_DL;								//actual level display list
};
