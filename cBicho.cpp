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

bool cBicho::MapCollidesUp(Matrix& map, float x, float y) {
	bool collides = false;

	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = (y + h) / TILE_SIZE;

	int width_tiles = w / TILE_SIZE;			// cuantos tiles ocupa Bicho
	if (fmod(x, TILE_SIZE) != 0) width_tiles++;	// si Bicho no esta donde empieza el tile, ocupara uno mas

	int i = 0;
	while ((i < width_tiles) && !collides) {
		if (map[tile_y][tile_x + i] != 0) {
			if (fmod(y, TILE_SIZE) != 0) {
				y = (tile_y + 1) * TILE_SIZE;
			}
			collides = true;
		}
		i++;
	}

	return collides;
}

bool cBicho::MapCollidesDown(Matrix& map, float x, float y) {
	bool collides = false;

	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;

	int width_tiles = w / TILE_SIZE;			// cuantos tiles ocupa Bicho
	if (fmod(x, TILE_SIZE) != 0) width_tiles++;	// si Bicho no esta donde empieza el tile, ocupara uno mas

	int i = 0;
	while ((i < width_tiles) && !collides) {
		if (map[tile_y][tile_x + i] != 0) {
			if (fmod(y, TILE_SIZE) != 0) {
				y = (tile_y + 1) * TILE_SIZE;
			}
			collides = true;
		}

		if (map[tile_y][tile_x + i] == 8) {
			char msgbuf[64];
			sprintf(msgbuf, "HIT [y,x]=[%d,%d]\n", tile_y, tile_x+i);
			OutputDebugStringA(msgbuf);
			HitEnemy();
		}
		i++;
	}

	return collides;
}

bool cBicho::MapCollidesLeft(Matrix& map, float x, float y) {
	bool collides = false;

	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;

	int height_tiles = h / TILE_SIZE;			// cuantos tiles ocupa Bicho
	if (fmod(y, TILE_SIZE) != 0) height_tiles++;	// si Bicho no esta donde empieza el tile, ocupara uno mas

	int i = 0;
	while ((i < height_tiles) && !collides) {
		if (map[tile_y + i][tile_x] != 0) {
			if (fmod(x, TILE_SIZE) != 0) {
				x = (tile_x + 1) * TILE_SIZE;
			}
			collides = true;
		}
		i++;
	}

	return collides;
}

bool cBicho::MapCollidesRight(Matrix& map, float x, float y) {
	bool collides = false;

	// tile al que corresponde
	int tile_x = (x + w) / TILE_SIZE;
	int tile_y = y / TILE_SIZE;

	int height_tiles = h / TILE_SIZE;			// cuantos tiles ocupa Bicho
	if (fmod(y, TILE_SIZE) != 0) height_tiles++;	// si Bicho no esta donde empieza el tile, ocupara uno mas

	int i = 0;
	while ((i < height_tiles) && !collides) {
		if (map[tile_y + i][tile_x] != 0) {
			if (fmod(x, TILE_SIZE) != 0) {
				x = (tile_x + 1) * TILE_SIZE;
			}
			collides = true;
		}
		i++;
	}

	return collides;
}

void cBicho::MoveLeft(Matrix& map) {
	for (int step_length = STEP_LENGTH; step_length > 0; --step_length) {
		float aux = x - step_length;

		if (aux - xWindow >= 0 && !MapCollidesLeft(map, aux, y)) {
			x = aux;
			return;
		}
	}
}

void cBicho::MoveRight(Matrix& map) {
	for (int step_length = STEP_LENGTH; step_length > 0; --step_length) {
		float aux = x + step_length;

		if (aux + w - xWindow < GAME_WIDTH && !MapCollidesRight(map, aux, y)) {
			x = aux;
			return;
		}
	}
}

void cBicho::MoveUp(Matrix& map) {
	for (int step_length = STEP_LENGTH; step_length > 0; --step_length) {
		float aux = y + step_length;

		if (aux+ h < GAME_HEIGHT-GAME_MARGIN && !MapCollidesUp(map, x, aux)) {
			y = aux;
			return;
		}
	}
}

void cBicho::MoveDown(Matrix& map) {
	for (int step_length = STEP_LENGTH; step_length > 0; --step_length) {
		float aux = y - step_length;

		if (aux >= 0 && !MapCollidesDown(map, x, aux)) {
			y = aux;
			return;
		}
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