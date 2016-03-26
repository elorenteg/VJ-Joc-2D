#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"

cBicho::cBicho(void) {
	seq = 0;
	delay = 0;
	xWindow = 0;
}

cBicho::~cBicho(void) {}

cBicho::cBicho(float posx, float posy, int width, int height) {
	x = posx;
	y = posy;
	w = width;
	h = height;
}

void cBicho::SetPosition(float posx, float posy) {
	x = posx;
	y = posy;
}

void cBicho::SetTile(int tx, int ty) {
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}

void cBicho::SetWidthHeight(int width, int height) {
	w = width;
	h = height;
}

void cBicho::SetX(float posX) {
	x = posX;
}

void cBicho::SetY(float posY) {
	y = posY;
}

void cBicho::SetXWindow(float xWind) {
	xWindow = xWind;
}

float cBicho::GetX() {
	return x;
}

float cBicho::GetY() {
	return y;
}

float cBicho::GetXWindow() {
	return xWindow;
}

int cBicho::GetWidth() {
	return w;
}

int cBicho::GetHeight() {
	return h;
}

void cBicho::DrawRect(int tex_id, float xo, float yo, float xf, float yf) {
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
		glTexCoord2f(xo, yo);	glVertex3f(x, y, SCENE_DEPTH);
		glTexCoord2f(xf, yo);	glVertex3f(x + w, y, SCENE_DEPTH);
		glTexCoord2f(xf, yf);	glVertex3f(x + w, y + h, SCENE_DEPTH);
		glTexCoord2f(xo, yf);	glVertex3f(x, y + h, SCENE_DEPTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

bool cBicho::MapCollidesUp(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_y_new = tile_y + BICHO_HEIGHT / TILE_SIZE;

	if (tile_y_new >= SCENE_HEIGHT) return true;
	else {
		//int width_tiles = w / TILE_SIZE;			// cuantos tiles ocupa Bicho
		//if (fmod(x, TILE_SIZE) != 0) width_tiles++;	// si Bicho no esta donde empieza el tile, ocupara uno mas

		for (int tx = tile_x; tx < tile_x + BICHO_WIDTH / TILE_SIZE; ++tx) {
			if (map[tile_y_new][tx] != 0) return true;

			if (isEnemy(map, tx, tile_y_new)) {
				char msgbuf[64];
				sprintf(msgbuf, "HIT [y,x]=[%d,%d]\n", tile_y_new, tx);
				OutputDebugStringA(msgbuf);
				HitEnemy();
			}
		}
		return false;
	}
}

bool cBicho::MapCollidesDown(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_y_new = tile_y - 1;

	if (tile_y_new < 0) return true;
	else {
		//int width_tiles = w / TILE_SIZE;			// cuantos tiles ocupa Bicho
		//if (fmod(x, TILE_SIZE) != 0) width_tiles++;	// si Bicho no esta donde empieza el tile, ocupara uno mas

		for (int tx = tile_x; tx < tile_x + BICHO_WIDTH / TILE_SIZE; ++tx) {
			if (map[tile_y_new][tx] != 0) return true;

			if (isEnemy(map, tx, tile_y_new)) {
				char msgbuf[64];
				sprintf(msgbuf, "HIT [y,x]=[%d,%d]\n", tile_y_new, tx);
				OutputDebugStringA(msgbuf);
				HitEnemy();
			}
		}
		return false;
	}
}

bool cBicho::MapCollidesLeft(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_x_new = tile_x - 1;

	if (x - step < xWindow) return true;
	else {
		//int width_tiles = w / TILE_SIZE;			// cuantos tiles ocupa Bicho
		//if (fmod(x, TILE_SIZE) != 0) width_tiles++;	// si Bicho no esta donde empieza el tile, ocupara uno mas

		for (int ty = tile_y; ty < tile_y + BICHO_HEIGHT / TILE_SIZE; ++ty) {
			if (map[ty][tile_x_new] != 0) return true;

			if (isEnemy(map, tile_x_new, ty)) {
				char msgbuf[64];
				sprintf(msgbuf, "HIT [y,x]=[%d,%d]\n", ty, tile_x_new);
				OutputDebugStringA(msgbuf);
				HitEnemy();
			}
		}
		return false;
	}
}

bool cBicho::MapCollidesRight(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_x_new = tile_x + BICHO_WIDTH/TILE_SIZE;

	char msgbuf2[64];
	sprintf(msgbuf2, "Right [tile_x,tile_x_new]=[%d,%d]\n", tile_x, tile_x_new);
	OutputDebugStringA(msgbuf2);

	if (x + BICHO_WIDTH + step >= xWindow + GAME_WIDTH) return true;
	else {
		//int width_tiles = w / TILE_SIZE;			// cuantos tiles ocupa Bicho
		//if (fmod(x, TILE_SIZE) != 0) width_tiles++;	// si Bicho no esta donde empieza el tile, ocupara uno mas

		for (int ty = tile_y; ty < tile_y + BICHO_HEIGHT / TILE_SIZE; ++ty) {
			if (map[ty][tile_x_new] != 0) return true;

			if (isEnemy(map, tile_x_new, ty)) {
				char msgbuf[64];
				sprintf(msgbuf, "HIT [y,x]=[%d,%d]\n", ty, tile_x_new);
				OutputDebugStringA(msgbuf);
				HitEnemy();
			}
		}
		return false;
	}
}

void cBicho::MoveLeft(Matrix& map) {
	for (int step = STEP_LENGTH; step > 0; step -= 0.2f) {
		if (!MapCollidesLeft(map, step)) {
			x = x - step;
			return;
		}
	}
}

void cBicho::MoveRight(Matrix& map) {
	for (int step = STEP_LENGTH; step > 0; step -= 0.2f) {
		if (!MapCollidesRight(map, step)) {
			x = x + step;
			return;
		}
	}
}

void cBicho::MoveUp(Matrix& map) {
	if (!MapCollidesUp(map, STEP_LENGTH)) {
		y = y + STEP_LENGTH;
	}
}

void cBicho::MoveDown(Matrix& map) {
	if (!MapCollidesDown(map, STEP_LENGTH)) {
		y = y - STEP_LENGTH;
	}
}

void cBicho::NextFrame(int max) {
	delay++;
	if (delay == FRAME_DELAY) {
		seq++;
		seq %= max;
		delay = 0;
	}
}

int cBicho::GetFrame() {
	return seq;
}

int cBicho::GetState() {
	return state;
}

void cBicho::SetState(int s) {
	state = s;
}

void cBicho::HitEnemy() {
	OutputDebugStringA("cBicho - HIT\n");
}

void cBicho::SetMapValue(Matrix& map, int tile_x, int tile_y, int value) {
	for (int i = tile_x; i < tile_x + BICHO_WIDTH / TILE_SIZE; ++i) {
		for (int j = tile_y; j < tile_y + BICHO_HEIGHT / TILE_SIZE; ++j) {
			map[j][i] = value;
		}
	}
}

bool cBicho::isEnemy(Matrix& map, int tile_x, int tile_y) {
	if (map[tile_y][tile_x] == ENEMY_VER - 48) return true;
	if (map[tile_y][tile_x] == ENEMY_HOR - 48) return true;
	if (map[tile_y][tile_x] == ENEMY_CIR - 48) return true;
	return false;
}