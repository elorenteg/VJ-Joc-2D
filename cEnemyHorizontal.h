#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	LEFT		0
#define CENTER_R	1
#define	RIGHT		2
#define	CENTER_L	3

#define FRAMES_MOVE	20

class cEnemyHorizontal : public cBicho
{
public:
	cEnemyHorizontal();
	~cEnemyHorizontal();

	void Draw(int tex_id);

	void Logic(Matrix& map);

private:
	int state;
	int time_state;
};
