#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"

cBicho::cBicho(void) {
	seq = 0;
	delay = 0;
}

cBicho::~cBicho(void) {}

cBicho::cBicho(int posx, int posy, int width, int height) {
	x = posx;
	y = posy;
	w = width;
	h = height;
}

void cBicho::SetPosition(int posx, int posy) {
	x = posx;
	y = posy;
}

void cBicho::GetPosition(int *posx, int *posy) {
	*posx = x;
	*posy = y;
}

void cBicho::SetTile(int tx, int ty) {
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}

void cBicho::GetTile(int *tx, int *ty) {
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}

void cBicho::SetWidthHeight(int width, int height) {
	w = width;
	h = height;
}

void cBicho::GetWidthHeight(int *width, int *height) {
	*width = w;
	*height = h;
}

bool cBicho::Collides(cRect *rc) {
	return ((x > rc->left) && (x + w<rc->right) && (y>rc->bottom) && (y + h < rc->top));
}

bool cBicho::CollidesMapWall(int *map, bool right) {
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if (right)	tile_x += width_tiles;

	for (j = 0; j < height_tiles; j++) 	{
		if (map[tile_x + ((tile_y + j)*SCENE_WIDTH)] != 0)	return true;
	}

	return false;
}

bool cBicho::CollidesMapFloor(int *map) {
	int tile_x, tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	if ((x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i = 0;
	while ((i < width_tiles) && !on_base) {
		if ((y % TILE_SIZE) == 0) {
			if (map[(tile_x + i) + ((tile_y - 1) * SCENE_WIDTH)] != 0)
				on_base = true;
		}
		else {
			if (map[(tile_x + i) + (tile_y * SCENE_WIDTH)] != 0) {
				y = (tile_y + 1) * TILE_SIZE;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}

void cBicho::GetArea(cRect *rc) {
	rc->left = x;
	rc->right = x + w;
	rc->bottom = y;
	rc->top = y + h;
}

void cBicho::DrawRect(int tex_id, float xo, float yo, float xf, float yf) {
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex2i(x, y);
	glTexCoord2f(xf, yo);	glVertex2i(x + w, y);
	glTexCoord2f(xf, yf);	glVertex2i(x + w, y + h);
	glTexCoord2f(xo, yf);	glVertex2i(x, y + h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

bool cBicho::insideWindow(Mapa map, int x, int y) {
	bool inside = true;

	if (x < 0 || y < 0) inside = false;
	else if (x + w > GAME_WIDTH) inside = false;
	else if (y + h > GAME_HEIGHT) inside = false;

	return inside;
}

bool cBicho::MapCollides(Mapa map, int x, int y) {
	bool collides = false;

	int tile_x, tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	if ((x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i = 0;
	while ((i < width_tiles) && !on_base) {
		if ((y % TILE_SIZE) == 0) {
			//if (map[(tile_x + i) + ((tile_y - 1) * SCENE_WIDTH)] != 0)
			//	on_base = true;
		}
		else {
			//if (map[(tile_x + i) + (tile_y * SCENE_WIDTH)] != 0) {
			//	y = (tile_y + 1) * TILE_SIZE;
			//	on_base = true;
			//}
		}
		i++;
	}

	return on_base;

	return collides;
}

void cBicho::MoveLeft(Mapa map) {
	// TODO: Mirar colision

	int aux = x - STEP_LENGTH;

	//if (!MapCollides(map, aux, y)) x -= STEP_LENGTH;
	if (insideWindow(map, aux, y)) x -= STEP_LENGTH;
}

void cBicho::MoveRight(Mapa map) {
	// TODO: Mirar colision

	int aux = x + STEP_LENGTH;

	if (insideWindow(map, aux, y)) x += STEP_LENGTH;
}

void cBicho::MoveUp(Mapa map) {
	int xaux;

	int aux = y + STEP_LENGTH;

	// TODO: Mirar colision

	if (insideWindow(map, x, aux)) y += STEP_LENGTH;
}

void cBicho::MoveDown(Mapa map) {
	int xaux;

	int aux = y - STEP_LENGTH;

	// TODO: Mirar colision

	if (insideWindow(map, x, aux) && !MapCollides(map, y, aux)) y -= STEP_LENGTH;
}

void cBicho::Logic(Mapa map) {
	float alfa;

	/*
	if (jumping) {
		jump_alfa += JUMP_STEP;

		if (jump_alfa == 180) {
			jumping = false;
			y = jump_y;
		}
		else {
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)(((float)JUMP_HEIGHT) * sin(alfa));

			if (jump_alfa > 90) {
				//Over floor?
				jumping = !CollidesMapFloor(map);
			}
		}
	}
	else {
		//Over floor? - gravedad!!
		if (!CollidesMapFloor(map))
			y -= (2 * STEP_LENGTH);
	}
	*/
}

void cBicho::NextFrame(int max) {
	delay++;
	if (delay == FRAME_DELAY) {
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