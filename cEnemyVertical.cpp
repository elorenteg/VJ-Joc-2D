#include "cEnemyVertical.h"

cEnemyVertical::cEnemyVertical() {
	state = rand() % MAX_MOVES;
	num_moves = rand() % TILES_MOVE;
	time_state = FRAMES_MOVE;
	state_lookat = DIR_LEFT;
	freq_shoots = FREQ_SHOOTS;

	state = UP;
	num_moves = TILES_MOVE;
}

cEnemyVertical::~cEnemyVertical() {}

void cEnemyVertical::Draw(int tex_id) {
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

void cEnemyVertical::Logic(Matrix& map, float cameraXSceneInc) {
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

	if (move) {
		int tile_y_new = (y + inc*TILE_SIZE) / TILE_SIZE;
		SetMapValue(map, tile_x, tile_y_new, ENEMY_VER - 48);
		SetTile(tile_x, tile_y_new);
	}
	else {
		SetMapValue(map, tile_x, tile_y, ENEMY_VER - 48);
	}

	xWindow += cameraXSceneInc;

	--freq_shoots;
	if (freq_shoots == 0) {
		freq_shoots = FREQ_SHOOTS;
		Shoot(map);
	}
}

int cEnemyVertical::maxFramesProjectiles() {
	return 4;
}