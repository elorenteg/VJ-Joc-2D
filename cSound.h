#pragma once
#pragma comment(lib, "fmodex_vc.lib" ) // fmod library

#include "Globals.h"

#include "fmod.hpp" //fmod c++ header

#define CHANGE_IN_MENU			0
#define SOUND_NYAN_BASE			1
#define SOUND_NYAN_BASE_8BIT	2
#define SOUND_CAT_SHOOT			3
#define SOUND_CAT_DYING			4
#define SOUND_ENEMY_SHOOT		5
#define SOUND_ENEMY_DEAD		6
#define SOUND_BOSS_SHOOT		7
#define SOUND_BOSS_DEAD			8

#define CHANNEL_MUSIC			100
#define CHANNEL_SHOOTS			101
#define CHANNEL_DEADS			102

class cSound
{
public:
	cSound(void);
	~cSound(void);

	void Update();

	//FMod Stuff
	FMOD::System     *system; //handle to FMOD engine
	FMOD::Sound      //sound that will be loaded and played
		*menu_change,
		*nyan_base,
		*nyan_base_8bit,
		*cat_shoot,
		*cat_dying,
		*enemy_shoot,
		*enemy_dead,
		*boss_shoot,
		*boss_dead;

	FMOD::Channel* channel_music;
	FMOD::Channel* channel_shoots;
	FMOD::Channel* channel_deads;

	bool playingMainBaseSound;
	bool playingMain8BITSound;

	void PlayCustomSound(int sound);
	void StopCustomChannel(int channelID);

private:

};
