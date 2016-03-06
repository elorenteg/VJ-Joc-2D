#pragma once

#include "cTexture.h"
#include "Globals.h"

#define SCENE_Xo		(2*TILE_SIZE)
#define SCENE_Yo		TILE_SIZE
#define SCENE_WIDTH		36
#define SCENE_HEIGHT	28

#define TILE_SIZE		16
#define BLOCK_SIZE		24

#define DEPTH			-5

class cMountainLayer {
public:
	cMountainLayer(void);
	virtual ~cMountainLayer(void);

	bool LoadMountain();
	void Draw(int tex_id);
	int *GetMap();

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int id_DL;								//actual level display list
};