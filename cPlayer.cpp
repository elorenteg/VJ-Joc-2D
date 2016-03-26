#include "cPlayer.h"

cPlayer::cPlayer() {}

cPlayer::~cPlayer() {}

void cPlayer::Draw(int tex_id) {
	float xo, yo, xf, yf;

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

void cPlayer::DrawRainbow(int tex_id, float xWindow) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	float x = GetX();
	float y = GetY();
	int h = GetHeight();

	float xo = 0.0f;
	float xf = 1.0f;
	float yo = 1.0f;
	float yf = 0.0f;

	int size_quad = 20;
	int count = 0;
	for (float i = xWindow; i < x + 15; i = i + size_quad) {
		glBegin(GL_QUADS);
			glTexCoord2f(xo, yo);	glVertex3f(i, y + count * 5, SCENE_DEPTH);
			glTexCoord2f(xf, yo);	glVertex3f(i + size_quad, y + count * 5, SCENE_DEPTH);
			glTexCoord2f(xf, yf);	glVertex3f(i + size_quad, y + h + count * 5, SCENE_DEPTH);
			glTexCoord2f(xo, yf);	glVertex3f(i, y + h + count * 5, SCENE_DEPTH);
		glEnd();

		++count;
		count = count % 2;
	}

	glDisable(GL_TEXTURE_2D);
}

bool cPlayer::isGameOver() {
	if (GetX() + GetWidth() - GetXWindow() < 20) return true;

	//if (lifes <= 0) return true;

	return false;
}

void cPlayer::Logic(Matrix& map, float cameraXSceneInc) {
	int tile_x = GetX() / TILE_SIZE;
	int tile_y = GetY() / TILE_SIZE;
	SetMapValue(map, tile_x, tile_y, 0);

	if (!MapCollidesRight(map, cameraXSceneInc)) SetX(GetX() + cameraXSceneInc);

	int tile_x_new = GetX() / TILE_SIZE;
	SetMapValue(map, tile_x_new, tile_y, PLAYER - 48);
	SetXWindow(GetXWindow() + cameraXSceneInc);
}

void cPlayer::HitEnemy() {
	char msgbuf[64];
	sprintf(msgbuf, "cPlayer - HIT %d lifes\n", lifes);
	OutputDebugStringA(msgbuf);
	lifes -= 1;
}