#include "cSound.h"

cSound::cSound(void)
{
	//init FMOD
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels

	system->createSound("Sound/menu_change.wav", FMOD_HARDWARE, 0, &menu_change);
	system->createSound("Sound/nyan_cat_base.wav", FMOD_HARDWARE, 0, &nyan_base);
	system->createSound("Sound/nyan_cat_base_8bit.mp3", FMOD_HARDWARE, 0, &nyan_base_8bit);
	system->createSound("Sound/cat_shoot.wav", FMOD_HARDWARE, 0, &cat_shoot);
	system->createSound("Sound/cat_dying.wav", FMOD_HARDWARE, 0, &cat_dying);
	system->createSound("Sound/enemy_shoot.wav", FMOD_HARDWARE, 0, &enemy_shoot);
	system->createSound("Sound/enemy_dead.wav", FMOD_HARDWARE, 0, &enemy_dead);
	system->createSound("Sound/boss_shoot.wav", FMOD_HARDWARE, 0, &boss_shoot);
	system->createSound("Sound/boss_dead.wav", FMOD_HARDWARE, 0, &boss_dead);
	//nyan_base->setMode(FMOD_LOOP_OFF);

	playingMainBaseSound = false;
	playingMain8BITSound = false;
}

cSound::~cSound(void)
{
}

void cSound::PlayCustomSound(int sound) {
	if (sound == CHANGE_IN_MENU) {
		system->playSound(FMOD_CHANNEL_FREE, menu_change, false, 0);
	}
	else if (sound == SOUND_NYAN_BASE) {
		if (channel_music->isPlaying(&playingMainBaseSound) == FMOD_OK && playingMainBaseSound) {
			channel_music->stop();
		}
		system->playSound(FMOD_CHANNEL_FREE, nyan_base, false, &channel_music);
	}
	else if (sound == SOUND_NYAN_BASE_8BIT) {
		if (channel_music->isPlaying(&playingMain8BITSound) == FMOD_OK && playingMain8BITSound) {
			channel_music->stop();
		}
		system->playSound(FMOD_CHANNEL_FREE, nyan_base_8bit, false, &channel_music);
	}
	else if (sound == SOUND_CAT_SHOOT) {
		system->playSound(FMOD_CHANNEL_FREE, cat_shoot, false, &channel_shoots);
	}
	else if (sound == SOUND_CAT_DYING) {
		system->playSound(FMOD_CHANNEL_FREE, cat_dying, false, &channel_deads);
	}
	else if (sound == SOUND_ENEMY_SHOOT) {
		system->playSound(FMOD_CHANNEL_FREE, enemy_shoot, false, &channel_shoots);
	}
	else if (sound == SOUND_ENEMY_DEAD) {
		system->playSound(FMOD_CHANNEL_FREE, enemy_dead, false, &channel_deads);
	}
	else if (sound == SOUND_BOSS_DEAD) {
		system->playSound(FMOD_CHANNEL_FREE, boss_dead, false, &channel_deads);
	}
	else if (sound == SOUND_BOSS_SHOOT) {
		system->playSound(FMOD_CHANNEL_FREE, boss_shoot, false, &channel_shoots);
	}
}

void cSound::StopCustomChannel(int channelID){
	FMOD::Channel* channel;
	if (channelID == CHANNEL_MUSIC) {
		channel = channel_music;
	}
	else if (channelID == CHANNEL_SHOOTS) {
		channel = channel_shoots;
	}
	else if (channelID == CHANNEL_DEADS) {
		channel = channel_deads;
	}

	bool isPlayingSomeSound = false;
	if (channel->isPlaying(&isPlayingSomeSound) == FMOD_OK && isPlayingSomeSound) {
		channel->stop();
	}
}

void cSound::Update() {
	system->update();
}