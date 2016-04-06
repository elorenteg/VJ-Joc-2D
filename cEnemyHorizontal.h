#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	LEFT		0
#define	RIGHT		1

#define FRAMES_MOVE	15
#define TILES_MOVE	4
#define MAX_MOVES	2

#define RANDOM_PONDERATION rand() % 10 + (-15)
#define FREQ_SHOOTS 100 + RANDOM_PONDERATION

class cEnemyHorizontal : public cBicho
{
public:
	cEnemyHorizontal();
	~cEnemyHorizontal();

	void Draw(int tex_id);

	void Logic(Matrix& map, float cameraXScene);
	bool LogicProjectiles(Matrix& map, int level, int total_levels);

protected:
	bool lookAtRight();

private:
	int num_moves;
	int time_state;

	int state;
	int moves[MAX_MOVES] = { LEFT, RIGHT };
};
