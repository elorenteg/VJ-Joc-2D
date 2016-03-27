#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"

cBicho::cBicho(void) {
	seq = 0;
	delay = 0;
	xWindow = 0;
	projectiles = vector<Projectile>(0);
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

void cBicho::SetZ(float posZ) {
	z = posZ;
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

vector<Projectile> cBicho::GetProjectiles() {
	return projectiles;
}

void cBicho::DrawRect(int tex_id, float xo, float yo, float xf, float yf) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex3f(x, y, z);
	glTexCoord2f(xf, yo);	glVertex3f(x + w, y, z);
	glTexCoord2f(xf, yf);	glVertex3f(x + w, y + h, z);
	glTexCoord2f(xo, yf);	glVertex3f(x, y + h, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cBicho::DrawProjectiles(int tex_id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	int w = PROJ_WIDTH;
	int h = PROJ_HEIGHT;

	float xo = 0.0f;
	float xf = 1.0f;
	float yo, yf;

	for (int i = 0; i < projectiles.size(); ++i) {
		float posx = projectiles[i].x;
		float posy = projectiles[i].y;

		switch (projectiles[i].state_color) {
			case FRAME_0:
				yo = 0.0f;
				yf = 0.2f;
				break;
			case FRAME_1:
				yo = 0.2f;
				yf = 0.4f;
				break;
			case FRAME_2:
				yo = 0.4f;
				yf = 0.6f;
				break;
			case FRAME_3:
				yo = 0.6f;
				yf = 0.8f;
				break;
			case FRAME_4:
				yo = 0.8f;
				yf = 1.0f;
				break;
			}

		glBegin(GL_QUADS);
		glTexCoord2f(xo, yo);	glVertex3f(posx, posy, z);
		glTexCoord2f(xf, yo);	glVertex3f(posx + w, posy, z);
		glTexCoord2f(xf, yf);	glVertex3f(posx + w, posy + h, z);
		glTexCoord2f(xo, yf);	glVertex3f(posx, posy + h, z);
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
}

bool cBicho::MapCollidesUp(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_y_new = (y + BICHO_HEIGHT) / TILE_SIZE;

	bool collides = false;
	if (tile_y_new >= SCENE_HEIGHT) collides = true;
	else {
		int width_tiles = w / TILE_SIZE;
		if (fmod(x, TILE_SIZE) != 0) width_tiles++;

		for (int tx = tile_x; tx < tile_x + width_tiles && !collides; ++tx) {
			if (map[tile_y_new][tx] != 0) collides = true;

			if (isEnemy(map, tx, tile_y_new)) {
				char msgbuf[64];
				sprintf(msgbuf, "HIT [y,x]=[%d,%d]\n", tile_y_new, tx);
				OutputDebugStringA(msgbuf);
				HitEnemy();
			}
		}
	}
	return collides;
}

bool cBicho::MapCollidesDown(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_y_new = (y - step) / TILE_SIZE;

	bool collides = false;
	if (tile_y_new < 0) collides = true;
	else {
		int width_tiles = w / TILE_SIZE;
		if (fmod(x, TILE_SIZE) != 0) width_tiles++;

		for (int tx = tile_x; tx < tile_x + width_tiles && !collides; ++tx) {
			if (map[tile_y_new][tx] != 0) collides = true;

			if (isEnemy(map, tx, tile_y_new)) {
				char msgbuf[64];
				sprintf(msgbuf, "HIT [y,x]=[%d,%d]\n", tile_y_new, tx);
				OutputDebugStringA(msgbuf);
				HitEnemy();
			}
		}
	}
	return collides;
}

bool cBicho::MapCollidesLeft(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_x_new = (x - step) / TILE_SIZE;

	bool collides = false;
	if (x - step < xWindow) collides = true;
	else {
		int height_tiles = h / TILE_SIZE;
		if (fmod(y, TILE_SIZE) != 0) height_tiles++;

		for (int ty = tile_y; ty < tile_y + height_tiles && !collides; ++ty) {
			if (map[ty][tile_x_new] != 0) collides = true;

			if (isEnemy(map, tile_x_new, ty)) {
				char msgbuf[64];
				sprintf(msgbuf, "HIT [y,x]=[%d,%d]\n", ty, tile_x_new);
				OutputDebugStringA(msgbuf);
				HitEnemy();
			}
		}
	}
	return collides;
}

bool cBicho::MapCollidesRight(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_x_new = (x + step + BICHO_WIDTH) / TILE_SIZE;

	bool collides = false;
	if (x + BICHO_WIDTH + step >= xWindow + GAME_WIDTH) collides = true;
	else {
		int height_tiles = h / TILE_SIZE;
		if (fmod(y, TILE_SIZE) != 0) height_tiles++;

		for (int ty = tile_y; ty < tile_y + height_tiles && !collides; ++ty) {
			if (map[ty][tile_x_new] != 0) collides = true;

			if (isEnemy(map, tile_x_new, ty)) {
				char msgbuf[64];
				sprintf(msgbuf, "HIT [y,x]=[%d,%d]\n", ty, tile_x_new);
				OutputDebugStringA(msgbuf);
				HitEnemy();
			}
		}
	}
	return collides;
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

void cBicho::Shoot(Matrix& map) {
	Projectile proj = InitShoot();
	proj.state_color = FRAME_0;
	proj.time_color = MAX_FRAMES*3;

	projectiles.push_back(proj);
}

Projectile cBicho::InitShoot() {
	Projectile proj;
	proj.x = x + 50;
	proj.y = y + BICHO_HEIGHT / 2;

	return proj;
}

void cBicho::MoveProjectiles(int dirX, int dirY) {
	for (int p = 0; p < projectiles.size(); ++p) {
		if (dirX != DIR_NONE) projectiles[p].x += dirX*TILE_SIZE / 2;
		if (dirY != DIR_NONE) projectiles[p].y += dirY*TILE_SIZE / 2;

		if (projectiles[p].x < 0 || projectiles[p].x + PROJ_WIDTH >= xWindow + GAME_WIDTH) {
			projectiles.erase(projectiles.begin() + p);
		}
		else if (projectiles[p].y < 0 || projectiles[p].y / TILE_SIZE >= SCENE_HEIGHT) {
			projectiles.erase(projectiles.begin() + p);
		}
		else {
			projectiles[p].time_color = (projectiles[p].time_color - 1);
			if (projectiles[p].time_color == 0) {
				projectiles[p].time_color = MAX_FRAMES * 3;
				projectiles[p].state_color = (projectiles[p].state_color + 1) % MAX_FRAMES;
			}
		}
	}
}