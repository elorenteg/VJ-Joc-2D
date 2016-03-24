#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	LEFT		0
#define UP			1
#define CENTER_R	2
#define	RIGHT		3
#define	DOWN		4
#define	CENTER_L	5

#define FRAMES_MOVE	15
#define TILES_MOVE	3
#define MAX_MOVES	6

class cEnemyCircle : public cBicho
{
public:
	cEnemyCircle();
	~cEnemyCircle();

	void Draw(int tex_id);

	void Logic(Matrix& map);

private:
	int num_moves;
	int time_state;

	int state;
	int moves[MAX_MOVES] = { LEFT, UP, CENTER_R, RIGHT, DOWN, CENTER_L };
};
