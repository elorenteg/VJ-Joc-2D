#pragma once

#include "cBicho.h"
#include "Globals.h"

class cPlayer : public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);
};
