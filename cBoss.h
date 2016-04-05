#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	UP			0
#define	DOWN		1

#define FRAMES_MOVE	30
#define TILES_MOVE	6
#define MAX_MOVES	2

#define FREQ_SHOOTS 40
#define RANG_RAFAGA	30
#define PROJ_SPEED	6

class cBoss : public cBicho
{
public:
	cBoss();
	~cBoss();

	void Draw(int tex_id);

	void Logic(Matrix& map, float cameraXScene);
	bool LogicProjectiles(Matrix& map, int level, int total_levels);

protected:
	void Shoot(Matrix& map);
	int maxFramesProjectiles();
	int maxFreqProjectiles(int level, int total_levels);

private:
	int num_moves;
	int time_state;
	int freq_shoots;
	int time_rafaga;
	bool isRafaga;

	int state;
	int moves[MAX_MOVES] = { UP, DOWN };
};
