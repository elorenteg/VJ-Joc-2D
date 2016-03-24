#include "cEnemyVertical.h"

cEnemyVertical::cEnemyVertical() {
	state = CENTER_D;
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
	switch (state) {
		case UP:
			if (time_state == 0) {
				state = CENTER_D;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			inc = -1;
			break;
		case CENTER_D:
			if (time_state == 0) {
				state = DOWN;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			inc = -1;
			break;
		case DOWN:
			if (time_state == 0) {
				state = CENTER_U;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			inc = 1;
			break;
		case CENTER_U:
			if (time_state == 0) {
				state = UP;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			inc = 1;
			break;
	}

	if ((y + inc) / TILE_SIZE < SCENE_HEIGHT) {
		map[tile_y][tile_x] = 0;
		map[(y + inc)/TILE_SIZE][tile_x] = ENEMY_VER-48;

		SetY(y + inc);
	}
}