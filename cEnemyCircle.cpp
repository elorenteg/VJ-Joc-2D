#include "cEnemyCircle.h"

cEnemyCircle::cEnemyCircle() {
	state = rand() % MAX_MOVES;
	num_moves = rand() % TILES_MOVE;
	time_state = FRAMES_MOVE;
	state_lookat = DIR_LEFT;
	freq_shoots = FREQ_SHOOTS;

	state = RIGHT;
	num_moves = TILES_MOVE;
}

cEnemyCircle::~cEnemyCircle() {}

void cEnemyCircle::Draw(int tex_id) {
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

bool cEnemyCircle::lookAtRight() {
	if (state == RIGHT || state == UP) return true;
	else return false;
}

void cEnemyCircle::Logic(Matrix& map, float cameraXSceneInc) {
	float incX = 0;
	float incY = 0;
	switch (moves[state]) {
		case UP:
			incY = 1;
			break;
		case DOWN:
			incY = -1;
			break;
		case LEFT:
			incX = -1;
			break;
		case RIGHT:
			incX = 1;
			break;
	}

	int tile_x = x / TILE_SIZE;
	int tile_y = y / TILE_SIZE;
	SetMapValue(map, tile_x, tile_y, 0);

	bool move = false;
	if (incY > 0) move = !MapCollidesUp(map, TILE_SIZE);
	else if (incY < 0) move = !MapCollidesDown(map, TILE_SIZE);
	else if (incX > 0) move = !MapCollidesRight(map, TILE_SIZE);
	else if (incX < 0) move = !MapCollidesLeft(map, TILE_SIZE);

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
		int tile_x_new = (x + incX*TILE_SIZE) / TILE_SIZE;
		int tile_y_new = (y + incY*TILE_SIZE) / TILE_SIZE;
		SetMapValue(map, tile_x_new, tile_y_new, ENEMY_CIR - 48);
		SetTile(tile_x_new, tile_y_new);
	}
	else {
		SetMapValue(map, tile_x, tile_y, ENEMY_CIR - 48);
	}

	xWindow += cameraXSceneInc;
}

bool cEnemyCircle::LogicProjectiles(Matrix& map, int level, int total_levels) {
	MoveProjectiles(map);

	bool enemyShoot = frequencyShoot(map, level, total_levels);

	return enemyShoot;
}

int cEnemyCircle::maxFramesProjectiles() {
	return 4;
}

TexCoords cEnemyCircle::ChildYCoords() {
	TexCoords tex;
	tex.yo = 1.0f / 3;
	tex.yf = 0.0f;

	return tex;
}