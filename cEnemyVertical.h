#pragma once

#include "cBicho.h"
#include "Globals.h"

#define	UP			0
#define CENTER_D	1
#define	DOWN		2
#define	CENTER_U	3

#define FRAMES_MOVE	20

class cEnemyVertical : public cBicho
{
public:
	cEnemyVertical();
	~cEnemyVertical();

	void Draw(int tex_id);

	void Logic(Matrix& map);

private:
	int state;
	int time_state;
};
