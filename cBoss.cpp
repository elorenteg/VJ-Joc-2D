#include "cBoss.h"

cBoss::cBoss() {
	state = rand() % MAX_MOVES;
	num_moves = rand() % TILES_MOVE;
	time_state = FRAMES_MOVE;
	state_lookat = DIR_LEFT;

	freq_shoots = FREQ_SHOOTS;
	speed_proj = PROJ_SPEED;

	state = UP;
	num_moves = TILES_MOVE;

	isRafaga = false;
	time_rafaga = RANG_RAFAGA;
}

cBoss::~cBoss() {}

void cBoss::Draw(int tex_id) {
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

void cBoss::Logic(Matrix& map, float cameraXSceneInc) {
	if (GetX() < GetXWindow()) return;

	float inc = 0;
	switch (moves[state]) {
	case UP:
		inc = 1;
		break;
	case DOWN:
		inc = -1;
		break;
	}

	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	SetMapValue(map, tile_x, tile_y, 0);

	bool move;
	if (inc > 0) move = !MapCollidesUp(map, TILE_SIZE);
	else move = !MapCollidesDown(map, TILE_SIZE);

	if (time_state == 0) {
		if (num_moves == 0) {
			++state;
			state = state % MAX_MOVES;
			num_moves = TILES_MOVE;
		}
		else --num_moves;
		time_state = FRAMES_MOVE;
	}
	else {
		--time_state;
		move = false;
	}

	//move = false;

	if (move && !isRafaga) {
		int tile_y_new = (y + inc*TILE_SIZE) / TILE_SIZE;
		SetMapValue(map, tile_x, tile_y_new, ENEMY_VER - 48);
		SetTile(tile_x, tile_y_new);
	}
	else {
		SetMapValue(map, tile_x, tile_y, ENEMY_VER - 48);
	}

	xWindow += cameraXSceneInc;
}

bool cBoss::LogicProjectiles(Matrix& map, int level, int total_levels) {
	bool bossShoot = false;

	MoveProjectiles(map);

	--freq_shoots;
	if (freq_shoots <= 0) {
		OutputDebugStringA("SHOOT\n");
		freq_shoots = maxFreqProjectiles(level, total_levels);

		if (canShoot()) {
			Shoot(map);
			bossShoot = true;
		}
		
		--time_rafaga;
		if (time_rafaga <= 0) {
			isRafaga = !isRafaga;
			if (isRafaga) time_rafaga = RANG_RAFAGA / 2;
			else time_rafaga = RANG_RAFAGA;
		}
	}

	return bossShoot;
}

int cBoss::maxFramesProjectiles() {
	return 4;
}

void cBoss::Shoot(Matrix& map) {
	if (canShoot()) {
		int ini, fi;
		if (isRafaga) {
			ini = -1;
			fi = 1;
		}
		else {
			ini = 0;
			fi = 0;
		}

		for (int type = ini; type <= fi; ++type) {
			Projectile proj = InitShoot();
			proj.state_color = FRAME_0;
			proj.time_color = PROJ_TIME;
			proj.time_stamp = 0;
			proj.type = type;

			if (lookAtRight()) projsRight.push_back(proj);
			else projsLeft.push_back(proj);
		}
	}
}

int cBoss::maxFreqProjectiles(int level, int total_levels) {
	float freq = float(level) / total_levels + xWindow / (SCENE_WIDTH * TILE_SIZE - GAME_WIDTH);
	freq = freq / 3;
	int freq_s = FREQ_SHOOTS - freq;

	if (xWindow <= x && x + w <= xWindow + GAME_WIDTH) {
		char msgbuf[128];
		sprintf(msgbuf, "FREQ - %f -- %d\n", freq, freq_s);
		OutputDebugStringA(msgbuf);
	}
	return freq_s;
}