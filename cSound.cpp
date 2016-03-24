#include "cSound.h"

cSound::cSound(void)
{
}

cSound::~cSound(void)
{
}

void cSound::PlayCustomSound(int sound) {
	if (sound == SOUND_NYAN_BASE) {
		PlaySound((LPCSTR) "Sound/nyan_cat_base.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
}

void cSound::StopCustomSound() {
	PlaySound(NULL, 0, 0);
}