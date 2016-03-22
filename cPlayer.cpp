#include "cPlayer.h"

cPlayer::cPlayer() {}

cPlayer::~cPlayer() {}

void cPlayer::Draw(int tex_id) {
	float xo, yo, xf, yf;

	/*
	switch (GetFrame()) {
	case FRAME_0:
	xo = 0.0f;
	xf = 0.165f;
	break;
	case FRAME_1:
	xo = 0.165f;
	xf = 0.3333f;
	break;
	case FRAME_2:
	xo = 0.3334f;
	xf = 0.5f;
	break;
	case FRAME_3:
	xo = 0.5001f;
	xf = 0.668f;
	break;
	case FRAME_4:
	xo = 0.669f;
	xf = 0.836f;
	break;
	case FRAME_5:
	xo = 0.838f;
	xf = 1.0f;
	break;
	}
	*/

	switch (GetFrame()) {
		case FRAME_0:
			xo = 0.0f;
			xf = 0.2f;
			break;
		case FRAME_1:
			xo = 0.2f;
			xf = 0.4f;
			break;
		case FRAME_2:
			xo = 0.4f;
			xf = 0.6f;
			break;
		case FRAME_3:
			xo = 0.6f;
			xf = 0.8f;
			break;
		case FRAME_4:
			xo = 0.8f;
			xf = 1.0f;
			break;
	}
	yo = 1.0f;
	yf = 0.0f;

	DrawRect(tex_id, xo, yo, xf, yf);

	NextFrame(5);
}

bool cPlayer::isGameOver() {
	if (GetX() + GetWidth() - GetXWindow() < 20) return true;

	return false;
}