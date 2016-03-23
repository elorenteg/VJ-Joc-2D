#pragma once

#include "cBicho.h"
#include "Globals.h"

class cEnemy : public cBicho
{
public:
	cEnemy();
	~cEnemy();

	void Draw(int tex_id);
	bool isGameOver();
};
