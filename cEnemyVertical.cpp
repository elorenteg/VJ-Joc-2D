#include "cEnemyVertical.h"

cEnemyVertical::cEnemyVertical() {
	state = CENTER_D;
	num_moves = TILES_MOVE;
	time_state = FRAMES_MOVE;
}

cEnemyVertical::~cEnemyVertical() {}

void cEnemyVertical::Draw(int tex_id) {
	//OutputDebugStringA("cEnemyVertical - Draw\n");
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

void cEnemyVertical::Logic(Matrix& map) {
	float x = GetX();
	float y = GetY();

	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;

	float inc = 0;
	switch (moves[state]) {
		case UP:
			inc = 1;
			break;
		case CENTER_D:
			inc = -1;
			break;
		case DOWN:
			inc = -1;
			break;
		case CENTER_U:
			inc = 1;
			break;
	}

	bool move = false;
	if (time_state == 0) {
		if (num_moves == 0) {
			++state;
			state = state % MAX_MOVES;
			num_moves = TILES_MOVE;
		}
		else --num_moves;
		time_state = FRAMES_MOVE;
		move = true;
	}
	else --time_state;

	inc *= TILE_SIZE / 2;

	if (move && (y + inc) / TILE_SIZE < SCENE_HEIGHT) {
		//map[tile_y][tile_x] = 0;
		//map[(y + inc)/TILE_SIZE][tile_x] = ENEMY_VER-48;

		SetY(y + inc);
	}
}