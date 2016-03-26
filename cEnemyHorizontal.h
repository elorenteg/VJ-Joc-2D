#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	LEFT		0
#define	RIGHT		1

#define FRAMES_MOVE	15
#define TILES_MOVE	4
#define MAX_MOVES	2

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
	int moves[MAX_MOVES] = { LEFT, RIGHT };
};
