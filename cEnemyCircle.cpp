#include "cEnemyCircle.h"

cEnemyCircle::cEnemyCircle() {
	state = CENTER_L;
	time_state = FRAMES_MOVE;
}

cEnemyCircle::~cEnemyCircle() {}

void cEnemyCircle::Draw(int tex_id) {
	//OutputDebugStringA("cEnemyHorizontal - Draw\n");
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

	if (state == RIGHT || state == CENTER_R || state == DOWN) {
		float aux = xo;
		xo = xf;
		xf = aux;
	}

	yo = 1.0f;
	yf = 0.0f;

	DrawRect(tex_id, xo, yo, xf, yf);

	NextFrame(5);
}

void cEnemyCircle::Logic(Matrix& map) {
	float x = GetX();
	float y = GetY();

	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;

	float incX = 0;
	float incY = 0;
	switch (state) {
		case LEFT:
			if (time_state == 0) {
				state = UP;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			incX = -1;
			break;
		case UP:
			if (time_state == 0) {
				state = CENTER_R;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			incY = -1;
			break;
		case CENTER_R:
			if (time_state == 0) {
				state = RIGHT;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			incX = 1;
			break;
		case RIGHT:
			if (time_state == 0) {
				state = DOWN;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			incX = 1;
			break;
		case DOWN:
			if (time_state == 0) {
				state = CENTER_L;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			incY = 1;
			break;
		case CENTER_L:
			if (time_state == 0) {
				state = LEFT;
				time_state = FRAMES_MOVE;
			}
			else --time_state;
			incX = -1;
			break;
	}

	if ((x + incX) / TILE_SIZE < SCENE_WIDTH && (y + incY) / TILE_SIZE < SCENE_HEIGHT) {
		//map[tile_y][tile_x] = 0;
		//map[(y + inc)/TILE_SIZE][tile_x] = ENEMY_HOR - 48;

		SetX(x + incX);
		SetY(y + incY);
	}
}