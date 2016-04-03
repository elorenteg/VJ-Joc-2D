#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	UP			0
#define	DOWN		1

#define FRAMES_MOVE	15
#define TILES_MOVE	4
#define MAX_MOVES	2

#define FREQ_SHOOTS 35

class cEnemyVertical : public cBicho
{
public:
	cEnemyVertical();
	~cEnemyVertical();

	void Draw(int tex_id);

	void Logic(Matrix& map, float cameraXScene);

protected:
	int maxFramesProjectiles();

private:
	int num_moves;
	int time_state;
	int freq_shoots;

	int state;
	int moves[MAX_MOVES] = { UP, DOWN };
};
