#include "cEnemyHorizontal.h"

cEnemyHorizontal::cEnemyHorizontal() {
	state = rand() % MAX_MOVES;
	num_moves = rand() % TILES_MOVE;
	time_state = FRAMES_MOVE;
	state_lookat = DIR_LEFT;
	freq_shoots = FREQ_SHOOTS;

	state = LEFT;
	num_moves = TILES_MOVE;
}

cEnemyHorizontal::~cEnemyHorizontal() {}

bool cEnemyHorizontal::lookAtRight() {
	if (state == RIGHT) return true;
	else return false;
}

void cEnemyHorizontal::Draw(int tex_id) {
	if (!definitiveDead) {
		float xo, yo, xf, yf;
		TexCoords tex;

		if (!isDead) tex = TextureCoordinates();
		else tex = BubblesTextureCoordinates();

		xo = tex.xo;
		xf = tex.xf;
		yo = tex.yo;
		yf = tex.yf;

		DrawRect(tex_id, xo, yo, xf, yf);

		int max_frames = MAX_FRAMES;
		if (isDead) max_frames = MAX_FRAMES_DEAD;
		NextFrame(max_frames);

		if (isDead && GetFrame() > FRAME_5) definitiveDead = true;
	}
}

void cEnemyHorizontal::Logic(Matrix& map, float cameraXSceneInc) {
	float inc = 0;
	switch (moves[state]) {
	case RIGHT:
		inc = 1;
		break;
	case LEFT:
		inc = -1;
		break;
	}

	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	SetMapValue(map, tile_x, tile_y, 0);

	bool move;
	if (inc > 0) move = !MapCollidesRight(map, TILE_SIZE);
	else move = !MapCollidesLeft(map, TILE_SIZE);

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

	if (move && !isDead) {
		int tile_x_new = (x + inc*TILE_SIZE) / TILE_SIZE;
		SetMapValue(map, tile_x_new, tile_y, ENEMY_HOR - 48);
		SetTile(tile_x_new, tile_y);
	}
	else {
		SetMapValue(map, tile_x, tile_y, ENEMY_HOR - 48);
	}

	xWindow+= cameraXSceneInc;
}

bool cEnemyHorizontal::LogicProjectiles(Matrix& map, int level, int total_levels) {
	MoveProjectiles(map);

	bool enemyShoot = frequencyShoot(map, level, total_levels);

	return enemyShoot;
}

TexCoords cEnemyHorizontal::ChildYCoords() {
	TexCoords tex;
	tex.yo = 2 * 1.0f / 3;
	tex.yf = 1.0f / 3;

	return tex;
}