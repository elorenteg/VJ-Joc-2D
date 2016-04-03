#include "cPlayer.h"

cPlayer::cPlayer() {
	state_lookat = DIR_RIGHT;
	Rainbow = vector<Position>(0);
	state_rainbow = SIZE_RAINBOW;
}

cPlayer::~cPlayer() {}

void cPlayer::Reset() {
	ResetLife();
}

void cPlayer::ResetLife() {
	projsLeft = vector<Projectile>(0);
	projsRight = vector<Projectile>(0);
	xWindow = 0.0f;

	Rainbow = vector<Position>(0);
	state_rainbow = SIZE_RAINBOW;
}

bool cPlayer::isOutsideWindow() {
	if (x + w - xWindow < 20) return true;

	return false;
}

bool cPlayer::isGameOver() {
	//if (lifes <= 0) return true;

	return false;
}

bool cPlayer::canMove(Matrix& map, int tx, int ty) {
	if (isScene(map, tx, ty)) return false;
	else return true;
}

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	float xo = 0.0f;
	float xf = 1.0f;
	float yo = 1.0f;
	float yf = 0.0f;

	int size_quad = TILE_SIZE;
	int count = 0;
	int num = 0;
	float yAnt = 0;
	for (int i = 0; i < Rainbow.size(); ++i) {
		float x = Rainbow[i].x;
		float y = Rainbow[i].y;

		if (yAnt == y) {
			++num;
			if (num == 5) {
				++count;
				num = 0;
			}
			count = count % 2;
		}
		else {
			yAnt = y;
			count = 0;
			num = 1;
		}

		glBegin(GL_QUADS);
		glTexCoord2f(xo, yo);	glVertex3f(x, (y+5) + count * 4, SCENE_DEPTH);
		glTexCoord2f(xf, yo);	glVertex3f(x + SIZE_RAINBOW, (y+5) + count * 4, SCENE_DEPTH);
		glTexCoord2f(xf, yf);	glVertex3f(x + SIZE_RAINBOW, (y+h-5) + count * 4, SCENE_DEPTH);
		glTexCoord2f(xo, yf);	glVertex3f(x, (y+h-5) + count * 4, SCENE_DEPTH);
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void cPlayer::Logic(Matrix& map, float cameraXSceneInc) {
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	SetMapValue(map, tile_x, tile_y, 0);

	if (!MapCollidesRight(map, cameraXSceneInc)) x += cameraXSceneInc;

	int tile_x_new = x / TILE_SIZE;
	SetMapValue(map, tile_x_new, tile_y, PLAYER - 48);
	xWindow += cameraXSceneInc;

	--state_rainbow;
	if (state_rainbow == 0) {
		state_rainbow = SIZE_RAINBOW;

		Position pos;
		if (Rainbow.size() == 0) {
			pos.x = GetX();
			pos.y = GetY();
			Rainbow.push_back(pos);
		}
		else {
			Position posAnt = Rainbow[Rainbow.size() - 1];
			if (posAnt.x < GetX() + 15) {
				while (posAnt.x + SIZE_RAINBOW < GetX() + 15) {
					pos.x = posAnt.x + SIZE_RAINBOW;
					pos.y = GetY();
					Rainbow.push_back(pos);
					posAnt = pos;
				}
			}
			else {
				while (posAnt.x - SIZE_RAINBOW > GetX() + 15) {
					pos.x = posAnt.x - SIZE_RAINBOW;
					pos.y = GetY();
					Rainbow.push_back(pos);
					posAnt = pos;
				}
			}
		}
	}
}

void cPlayer::LogicProjectiles(Matrix& map) {
	MoveProjectiles(map);
}