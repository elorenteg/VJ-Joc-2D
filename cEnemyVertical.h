#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	UP			0
#define CENTER_D	1
#define	DOWN		2
#define	CENTER_U	3

#define FRAMES_MOVE	15
#define TILES_MOVE	3
#define MAX_MOVES	4

class cEnemyVertical : public cBicho
{
public:
	cEnemyVertical();
	~cEnemyVertical();

	void Draw(int tex_id);

	void Logic(Matrix& map);

private:
	int num_moves;
	int time_state;

	int state;
	int moves[MAX_MOVES] = { UP, CENTER_D, DOWN, CENTER_U };
};
