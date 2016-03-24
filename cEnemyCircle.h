#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	LEFT		0
#define UP			1
#define CENTER_R	2
#define	RIGHT		3
#define	DOWN		4
#define	CENTER_L	5

#define FRAMES_MOVE	20

class cEnemyCircle : public cBicho
{
public:
	cEnemyCircle();
	~cEnemyCircle();

	void Draw(int tex_id);

	void Logic(Matrix& map);

private:
	int state;
	int time_state;
};
