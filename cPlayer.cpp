#include "cPlayer.h"

cPlayer::cPlayer() {
	lifes = 3;
	score = 0;
	state_lookat = DIR_RIGHT;
}

cPlayer::~cPlayer() {}

void cPlayer::Reset() {
	lifes = 3;
	score = 0;

	ResetLife();
}

void cPlayer::ResetLife() {
	projsLeft = vector<Projectile>(0);
	projsRight = vector<Projectile>(0);
	xWindow = 0.0f;
}

int cPlayer::GetScore() {
	return score;
}

int cPlayer::GetLifes() {
	return lifes;
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
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	float xo = 0.0f;
	float xf = 1.0f;
	float yo = 1.0f;
	float yf = 0.0f;

	int size_quad = TILE_SIZE;
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
	//if (x + w - xWindow < 20) return true;

	if (lifes <= 0) return true;

	return false;
}

void cPlayer::Logic(Matrix& map, float cameraXSceneInc) {
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	SetMapValue(map, tile_x, tile_y, 0);

	if (!MapCollidesRight(map, cameraXSceneInc)) x += cameraXSceneInc;

	int tile_x_new = x / TILE_SIZE;
	SetMapValue(map, tile_x_new, tile_y, PLAYER - 48);
	xWindow += cameraXSceneInc;

	if (x + w - xWindow < 20) --lifes;
}

void cPlayer::HitEnemy() {
	char msgbuf[64];
	sprintf(msgbuf, "cPlayer - HIT %d lifes\n", lifes);
	OutputDebugStringA(msgbuf);
	//lifes -= 1;
}

Projectile cPlayer::InitShoot() {
	Projectile proj;
	proj.x = x + 50;
	proj.y = y + BICHO_HEIGHT / 2;

	return proj;
}

void cPlayer::LogicProjectiles(Matrix& map, vector<cEnemyVertical>& vers, vector<cEnemyHorizontal>& hors, vector<cEnemyCircle>& cirs) {
	MoveProjectiles();

	HitProjectile(map, vers);
	HitProjectile(map, hors);
	HitProjectile(map, cirs);
}

void cPlayer::HitProjectile(Matrix& map, vector<cEnemyVertical>& vers) {
	for (int p = 0; p < projsRight.size(); ++p) {
		int tx = projsRight[p].x / TILE_SIZE;
		int ty = projsRight[p].y / TILE_SIZE;
		int tx2 = tx + 1;

		if (isEnemy(map, tx, ty) || (projsRight[p].x + PROJ_WIDTH >= xWindow + GAME_WIDTH && isEnemy(map, tx2, ty))) {
			bool found = false;
			for (int v = 0; v < vers.size() && !found; ++v) {
				int v_tx = vers[v].GetX() / TILE_SIZE;
				int v_ty = vers[v].GetY() / TILE_SIZE;
				int v_tx2 = (vers[v].GetX() + vers[v].GetWidth()) / TILE_SIZE;
				int v_ty2 = (vers[v].GetY() + vers[v].GetHeight()) / TILE_SIZE;

				if (((tx >= v_tx && tx <= v_tx2) || (tx2 >= v_tx && tx2 <= v_tx2)) && ty >= v_ty && ty <= v_ty2) {
					found = true;
					vers.erase(vers.begin() + v);
					projsRight.erase(projsRight.begin() + p);
					SetMapValue(map, v_tx, v_ty, 0);
					++score;
				}
			}
		}
	}
}

void cPlayer::HitProjectile(Matrix& map, vector<cEnemyHorizontal>& hors) {
	for (int p = 0; p < projsRight.size(); ++p) {
		int tx = projsRight[p].x / TILE_SIZE;
		int ty = projsRight[p].y / TILE_SIZE;
		int tx2 = tx + 1;

		if (isEnemy(map, tx, ty) || (projsRight[p].x + PROJ_WIDTH >= xWindow + GAME_WIDTH && isEnemy(map, tx2, ty))) {
			bool found = false;
			for (int v = 0; v < hors.size() && !found; ++v) {
				int v_tx = hors[v].GetX() / TILE_SIZE;
				int v_ty = hors[v].GetY() / TILE_SIZE;
				int v_tx2 = (hors[v].GetX() + hors[v].GetWidth()) / TILE_SIZE;
				int v_ty2 = (hors[v].GetY() + hors[v].GetHeight()) / TILE_SIZE;

				if (((tx >= v_tx && tx <= v_tx2) || (tx2 >= v_tx && tx2 <= v_tx2)) && ty >= v_ty && ty <= v_ty2) {
					found = true;
					hors.erase(hors.begin() + v);
					projsRight.erase(projsRight.begin() + p);
					SetMapValue(map, v_tx, v_ty, 0);
					++score;
				}
			}
		}
	}
}

void cPlayer::HitProjectile(Matrix& map, vector<cEnemyCircle>& cirs) {
	for (int p = 0; p < projsRight.size(); ++p) {
		int tx = projsRight[p].x / TILE_SIZE;
		int ty = projsRight[p].y / TILE_SIZE;
		int tx2 = tx + 1;

		if (isEnemy(map, tx, ty) || (projsRight[p].x + PROJ_WIDTH >= xWindow + GAME_WIDTH && isEnemy(map, tx2, ty))) {
			bool found = false;
			for (int v = 0; v < cirs.size() && !found; ++v) {
				int v_tx = cirs[v].GetX() / TILE_SIZE;
				int v_ty = cirs[v].GetY() / TILE_SIZE;
				int v_tx2 = (cirs[v].GetX() + cirs[v].GetWidth()) / TILE_SIZE;
				int v_ty2 = (cirs[v].GetY() + cirs[v].GetHeight()) / TILE_SIZE;

				if (((tx >= v_tx && tx <= v_tx2) || (tx2 >= v_tx && tx2 <= v_tx2)) && ty >= v_ty && ty <= v_ty2) {
					found = true;
					cirs.erase(cirs.begin() + v);
					projsRight.erase(projsRight.begin() + p);
					SetMapValue(map, v_tx, v_ty, 0);
					++score;
				}
			}
		}
	}
}