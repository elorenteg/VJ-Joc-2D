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

	incX *= TILE_SIZE;
	incY *= TILE_SIZE;

	if (move && (x + incX) / TILE_SIZE < SCENE_WIDTH && (y + incY) / TILE_SIZE < SCENE_HEIGHT) {
		//map[tile_y][tile_x] = 0;
		//map[(y + inc)/TILE_SIZE][tile_x] = ENEMY_HOR - 48;

		SetX(x + incX);
		SetY(y + incY);
	}
}