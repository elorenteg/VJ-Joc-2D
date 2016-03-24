#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	LEFT		0
#define CENTER_R	1
#define	RIGHT		2
#define	CENTER_L	3

#define FRAMES_MOVE	15
#define TILES_MOVE	3
#define MAX_MOVES	4

class cEnemyHorizontal : public cBicho
{
public:
	cEnemyHorizontal();
	~cEnemyHorizontal();

	void Draw(int tex_id);

	void Logic(Matrix& map);

private:
	int num_moves;
	int time_state;

	int state;
	int moves[MAX_MOVES] = { LEFT, CENTER_R, RIGHT, CENTER_L };
};
