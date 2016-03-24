#include "cEnemyCircle.h"

cEnemyCircle::cEnemyCircle() {
	state = CENTER_L;
	num_moves = TILES_MOVE;
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

	if (state == RIGHT || state == CENTER_R || state == UP) {
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
	switch (moves[state]) {
		case LEFT:
			incY = -1;
			break;
		case UP:
			incX = 1;
			break;
		case CENTER_R:
			incY = 1;
			break;
		case RIGHT:
			incY = 1;
			break;
		case DOWN:
			incX = -1;
			break;
		case CENTER_L:
			incY = -1;
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


	if (move && (x + incX) / TILE_SIZE < SCENE_WIDTH && (y + incY) / TILE_SIZE < SCENE_HEIGHT) {
		for (int i = tile_x; i < tile_x + BICHO_WIDTH / TILE_SIZE; ++i) {
			for (int j = tile_y; j < tile_y + BICHO_HEIGHT / TILE_SIZE; ++j) {
				//map[j][i] = 0;
			}
		}

		for (int i = tile_x + incX; i < tile_x + BICHO_WIDTH / TILE_SIZE; ++i) {
			for (int j = tile_y + incY; j < tile_y + BICHO_HEIGHT / TILE_SIZE; ++j) {
				//map[j][i] = ENEMY_VER - 48;
			}
		}

		SetX(x + incX * TILE_SIZE);
		SetY(y + incY * TILE_SIZE);
	}
}