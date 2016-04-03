#pragma once

#include "Globals.h"

#define SOUND_NYAN_BASE		0
#define SOUND_CAT_DYING		1

class cSound
{
public:
	cSound(void);
	~cSound(void);

	void PlayCustomSound(int sound);
	void StopCustomSound();

private:

};
