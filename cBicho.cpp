#include "cBicho.h"
#include "cPlayer.h"
#include "cScene.h"
#include "Globals.h"

cBicho::cBicho(void) {
	seq = 0;
	delay = 0;
	xWindow = 0;
	projsLeft = vector<Projectile>(0);
	projsRight = vector<Projectile>(0);
	w_proj = PROJ_WIDTH;
	h_proj = PROJ_HEIGHT;
	speed_proj = PROJ_SPEED;
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

void cBicho::SetProjectiles(vector<Projectile>& projs, int dir) {
	if (dir == DIR_RIGHT) {
		projsRight = projs;
	}
	else {
		projsLeft = projs;
	}
}

void cBicho::SetWidthHeightProjectiles(int width, int height) {
	w_proj = width;
	h_proj = height;
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

vector<Projectile> cBicho::GetProjectiles(int dir) {
	if (dir == DIR_LEFT) return projsLeft;
	if (dir == DIR_RIGHT) return projsRight;
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

	DrawProjectiles(tex_id, projsLeft, DIR_LEFT);
	DrawProjectiles(tex_id, projsRight, DIR_RIGHT);

	glDisable(GL_TEXTURE_2D);
}

void cBicho::DrawProjectiles(int tex_id, vector<Projectile>& projectiles, int dir) {
	int w = w_proj;
	int h = h_proj;

	float xo = 0.0f;
	float xf = 1.0f;
	float yo, yf;

	int tex_y[MAX_MOVES] = { LEFT, UP, RIGHT, DOWN };

	for (int i = 0; i < projectiles.size(); ++i) {
		float posx = projectiles[i].x;
		float posy = projectiles[i].y;

		xo = xo_coords(projectiles[i].state_color, dir);
		xf = xf_coords(projectiles[i].state_color, dir);

		yo = yo_coords(projectiles[i].state_color);
		yf = yf_coords(projectiles[i].state_color);

		glBegin(GL_QUADS);
			glTexCoord2f(xo, yo);	glVertex3f(posx, posy, z);
			glTexCoord2f(xf, yo);	glVertex3f(posx + w, posy, z);
			glTexCoord2f(xf, yf);	glVertex3f(posx + w, posy + h, z);
			glTexCoord2f(xo, yf);	glVertex3f(posx, posy + h, z);
		glEnd();
	}
}

float cBicho::xo_coords(int state_color, int dir) {
	float xo;
	if (dir == DIR_LEFT) xo = 0.0f;
	else xo = 1.0f;

	return xo;
}

float cBicho::xf_coords(int state_color, int dir) {
	float xf;
	if (dir == DIR_LEFT) xf = 1.0f;
	else xf = 0.0f;

	return xf;
}

float cBicho::yo_coords(int state_color) {
	float yo = 1.0f / maxFramesProjectiles() * state_color + 1.0f / maxFramesProjectiles();

	return yo;
}

float cBicho::yf_coords(int state_color) {
	float yf = 1.0f / maxFramesProjectiles() * state_color;

	return yf;
}

bool cBicho::canMove(Matrix& map, int tx, int ty) {
	if (map[ty][tx] != 0) return false;
	else return true;
}

bool cBicho::MapCollidesUp(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_y_new = (y + h) / TILE_SIZE;

	bool collides = false;
	if (tile_y_new >= SCENE_HEIGHT) collides = true;
	else {
		int width_tiles = w / TILE_SIZE;
		if (fmod(x, TILE_SIZE) != 0) width_tiles++;

		for (int tx = tile_x; tx < tile_x + width_tiles && !collides; ++tx) {
			if (!canMove(map,tx,tile_y_new)) collides = true;
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
			if (!canMove(map, tx, tile_y_new)) collides = true;
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
			if (!canMove(map, tile_x_new, ty)) collides = true;
		}
	}
	return collides;
}

bool cBicho::MapCollidesRight(Matrix& map, float step) {
	// tile al que corresponde
	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	int tile_x_new = (x + step + w) / TILE_SIZE;

	bool collides = false;
	if (x + w + step >= xWindow + GAME_WIDTH) collides = true;
	else {
		int height_tiles = h / TILE_SIZE;
		if (fmod(y, TILE_SIZE) != 0) height_tiles++;

		for (int ty = tile_y; ty < tile_y + height_tiles && !collides; ++ty) {
			if (!canMove(map, tile_x_new, ty)) collides = true;
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

void cBicho::SetMapValue(Matrix& map, int tile_x, int tile_y, int value) {
	for (int i = tile_x; i < tile_x + w / TILE_SIZE; ++i) {
		for (int j = tile_y; j < tile_y + h / TILE_SIZE; ++j) {
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

bool cBicho::isScene(Matrix& map, int tile_x, int tile_y) {
	if (map[tile_y][tile_x] == GROUND) return true;
	if (map[tile_y][tile_x] == CLOUD_SUP_ESQ) return true;
	if (map[tile_y][tile_x] == CLOUD_SUP_CEN) return true;
	if (map[tile_y][tile_x] == CLOUD_SUP_DRE) return true;
	if (map[tile_y][tile_x] == CLOUD_INF_ESQ) return true;
	if (map[tile_y][tile_x] == CLOUD_INF_CEN) return true;
	if (map[tile_y][tile_x] == CLOUD_INF_DRE) return true;
	return false;
}

void cBicho::Shoot(Matrix& map) {
	if (canShoot()) {
		Projectile proj = InitShoot();
		proj.state_color = FRAME_0;
		proj.time_color = PROJ_TIME;
		proj.time_stamp = 0;
		proj.type = DIR_NONE;

		if (lookAtRight()) projsRight.push_back(proj);
		else projsLeft.push_back(proj);
	}
}

Projectile cBicho::InitShoot() {
	Projectile proj;
	if (lookAtRight()) proj.x = (x+w) + 10;
	else proj.x = x - 10;
	proj.y = y + (h-h_proj) / 2;

	return proj;
}

bool cBicho::lookAtRight() {
	return state_lookat == DIR_RIGHT;
}

bool cBicho::isInScene() {
	bool isInside = true;
	if (x < xWindow || x + w >= xWindow + GAME_WIDTH) isInside = false;

	return isInside;
}

void cBicho::MoveProjectiles(Matrix& map) {
	projsLeft = MoveProjectiles(map, projsLeft, DIR_LEFT);
	projsRight = MoveProjectiles(map, projsRight, DIR_RIGHT);
}

vector<Projectile> cBicho::MoveProjectiles(Matrix& map, vector<Projectile>& projs, int dirX) {
	for (int p = 0; p < projs.size(); ++p) {
		projs[p].x += dirX * speed_proj;

		if (projs[p].type != DIR_NONE) {
			if (projs[p].type > 0) {
				if (projs[p].time_stamp < 20) {
					projs[p].y += 3;
				}
			}
			else {
				if (projs[p].time_stamp < 20) {
					projs[p].y -= 3;
				}
			}
		}

		projs[p].time_stamp += 1;

		if (projs[p].x < 0 || projs[p].x + w_proj >= xWindow + GAME_WIDTH ||
			projs[p].y < 0 || projs[p].y + h_proj >= GAME_HEIGHT - GAME_MARGIN) {
			// proyectiles fuera de escena se eliminan
			projs.erase(projs.begin() + p);
		}
		else {
			// proyectiles dentro de escena
			int tile_x = projs[p].x / TILE_SIZE;
			int tile_y = projs[p].y / TILE_SIZE;
			int width_tiles = w_proj / TILE_SIZE;

			bool hitScene = false;
			for (int tx = tile_x; tx < tile_x + width_tiles; ++tx) {
				if (isScene(map, tx, tile_y)) hitScene = true;
			}

			if (hitScene) projs.erase(projs.begin() + p);
			else {
				projs[p].time_color = (projs[p].time_color - 1);
				if (projs[p].time_color == 0) {
					// cambio de color de gradiente
					projs[p].time_color = PROJ_TIME;
					projs[p].state_color = (projs[p].state_color + 1) % maxFramesProjectiles();
				}
			}
		}
	}
	return projs;
}

bool cBicho::LogicProjectiles(Matrix& map, int level, int total_levels) {
	OutputDebugStringA("Hola\n");

	return false;
}

void cBicho::Logic(Matrix& map, float cameraXScene) {
	OutputDebugStringA("NO :(");
}


void cBicho::Draw(int tex_id) {
	OutputDebugStringA("NO :(");
}

int cBicho::maxFramesProjectiles() {
	return 5;
}

int cBicho::maxFreqProjectiles(int level, int total_levels) {
	float freq = float(level) / total_levels + xWindow / (SCENE_WIDTH * TILE_SIZE - GAME_WIDTH);
	freq = freq / 3;
	int freq_s = FREQ_SHOOTS - freq * FREQ_SHOOTS;

	return freq_s;
}

bool cBicho::canShoot() {
	if (xWindow <= x + w/3 && x + w/3 <= xWindow + GAME_WIDTH - GAME_MARGIN) return true;

	return false;
}