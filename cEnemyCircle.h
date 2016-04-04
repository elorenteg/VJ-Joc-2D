#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	LEFT		0
#define UP			1
#define	RIGHT		2
#define	DOWN		3

#define FRAMES_MOVE	15
#define TILES_MOVE	6
#define MAX_MOVES	4

#define FREQ_SHOOTS 100

class cEnemyCircle : public cBicho
{
public:
	cEnemyCircle();
	~cEnemyCircle();

	void Draw(int tex_id);

	void Logic(Matrix& map, float cameraXScene);
	bool LogicProjectiles(Matrix& map, int level, int total_levels);

protected:
	bool lookAtRight();
	int maxFramesProjectiles();

private:
	int num_moves;
	int time_state;
	int freq_shoots;

	int state;
	int moves[MAX_MOVES] = { LEFT, UP, RIGHT, DOWN };
};
