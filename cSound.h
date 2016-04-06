#pragma once
#pragma comment(lib, "fmodex_vc.lib" ) // fmod library

#include "Globals.h"

#include "fmod.hpp" //fmod c++ header

#define CHANGE_IN_MENU		0
#define SOUND_NYAN_BASE		1
#define SOUND_CAT_SHOOT		2
#define SOUND_CAT_DYING		3
#define SOUND_ENEMY_DEAD	4
#define SOUND_BOSS_SHOOT	5
#define SOUND_BOSS_DEAD		6

class cSound
{
public:
	cSound(void);
	~cSound(void);

	//FMod Stuff
	FMOD::System     *system; //handle to FMOD engine
	FMOD::Sound      //sound that will be loaded and played
		*menu_change,
		*nyan_base,
		*cat_shoot,
		*cat_dying,
		*enemy_dead,
		*boss_shoot,
		*boss_dead;

	FMOD::Channel* channel_music;
	FMOD::Channel* channel_shoots;
	FMOD::Channel* channel_deads;

	bool playingMainSound;

	void PlayCustomSound(int sound);
	void StopCustomChannel(FMOD::Channel* channel);

private:

};
