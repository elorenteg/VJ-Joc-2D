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
	isDead = false;
	definitiveDead = false;
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

void cBicho::SetIsDead(bool dead) {
	isDead = dead;

	seq = FRAME_0;
	int wNew = 3 * TILE_SIZE;
	int hNew = 2 * TILE_SIZE;

	x = x + (w - wNew) / 2.0f;
	y = y + (h - hNew) / 2.0f;

	w = wNew;
	h = hNew;
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

bool cBicho::GetIsDead() {
	return isDead;
}

int cBicho::GetWProj() {
	return w_proj;
}

int cBicho::GetHProj() {
	return h_proj;
}

TexCoords cBicho::TextureCoordinates() {
	float xo, xf;

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

	if (!lookAtRight()) {
		float aux = xo;
		xo = xf;
		xf = aux;
	}

	TexCoords tex;
	tex.xo = xo;
	tex.xf = xf;

	tex.yo = 1.0f;
	tex.yf = 0.0f;

	return tex;
}

TexCoords cBicho::BubblesTextureCoordinates() {
	float xo, xf;

	xo = 1.0f / MAX_FRAMES_DEAD * GetFrame();
	xf = xo + 0.125f;

	TexCoords tex;
	tex.xo = xo;
	tex.xf = xf;

	TexCoords tex2 = ChildYCoords();
	tex.yo = tex2.yo;
	tex.yf = tex2.yf;

	return tex;
}

TexCoords cBicho::ChildYCoords() {
	TexCoords tex;
	return tex;
}

void cBicho::DrawRect(int tex_id, float xo, float yo, float xf, float yf) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex3f(x, y, z);
	glTexCoord2f(xf, yo);	glVertex3f(x + w, y, z);
	glTexCoord2f(xf, yf);	glVertex3f(x + w, y + h, z);
	glTexCoord2f(xo, yf);	glVertex3f(x, y + h, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
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
	if (!canMove(step)) collides = true;
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
	if (!canMove(step)) collides = true;
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
		if (x-step >= xWindow && !MapCollidesLeft(map, step)) {
			x = x - step;
			return;
		}
	}
}

void cBicho::MoveRight(Matrix& map) {
	for (int step = STEP_LENGTH; step > 0; step -= 0.2f) {
		if (x + w + step <= xWindow + GAME_WIDTH && !MapCollidesRight(map, step)) {
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
	int frame_delay = FRAME_DELAY;
	if (isDead) frame_delay = int(FRAME_DELAY / 3.0f);

	delay++;
	if (delay >= frame_delay) {
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
	if (map[tile_y][tile_x] == GRASS) return true;
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
					projs[p].y += 4;
				}
			}
			else {
				if (projs[p].time_stamp < 20) {
					projs[p].y -= 4;
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
			int tile_x = (projs[p].x / TILE_SIZE);
			int tile_y = (projs[p].y / TILE_SIZE);

			int width_tiles = (double(w_proj) / TILE_SIZE);
			int height_tiles = ceil(double(h_proj) / TILE_SIZE);

			if (fmod(projs[p].x, TILE_SIZE) != 0) width_tiles++;
			if (fmod(projs[p].y, TILE_SIZE) != 0) height_tiles++;

			bool hitScene = false;
			float xScene, yScene;
			for (int tx = tile_x; tx < tile_x + width_tiles; ++tx) {
				for (int ty = tile_y; ty < tile_y + height_tiles; ++ty) {
					if (isScene(map, tx, ty)) {
						xScene = tx*TILE_SIZE;
						yScene = ty*TILE_SIZE;

						bool notCollision = false;
						if (yScene + TILE_SIZE < projs[p].y || projs[p].y + h_proj < yScene) notCollision = true;
						if (xScene + TILE_SIZE < projs[p].x || projs[p].x + w_proj < xScene) notCollision = true;

						hitScene = !notCollision;
					}
				}
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

	return false;
}

void cBicho::Logic(Matrix& map, float cameraXScene) {

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
	if (x + w / 2 >= xWindow && x + w - w / 2 <= xWindow + GAME_WIDTH) return true;

	return false;
}

bool cBicho::canMove(float step) {
	//int stp = step;
	//if (!lookAtRight()) stp = -1 * stp;

	if (x + w - step < xWindow || x > xWindow + GAME_WIDTH) return false;
	//if (x + w + step < xWindow) return false;
	//
	//if (x > xWindow + GAME_WIDTH) return false;

	return true;
}

bool cBicho::frequencyShoot(Matrix& map, int level, int total_levels) {
	bool enemyShoot = false;
	if (!isDead) {
		--freq_shoots;
		if (freq_shoots <= 0) {
			freq_shoots = maxFreqProjectiles(level, total_levels);

			if (canShoot()) {
				Shoot(map);
				enemyShoot = true;
			}
		}
	}

	return enemyShoot;
}