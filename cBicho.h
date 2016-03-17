#pragma once

#include "cTexture.h"
#include "Globals.h"

#define FRAME_DELAY		10
#define STEP_LENGTH		2

#define FRAME_0		0
#define FRAME_1		1
#define FRAME_2		2
#define FRAME_3		3
#define FRAME_4		4
#define FRAME_5		5

class cRect
{
public:
	int left, top, right, bottom;
};

class cBicho
{
public:
	cBicho(void);
	cBicho(int x, int y, int w, int h);
	~cBicho(void);

	void SetPosition(int x, int y);
	void GetPosition(int *x, int *y);
	void SetTile(int tx, int ty);
	void GetTile(int *tx, int *ty);
	void SetWidthHeight(int w, int h);
	void GetWidthHeight(int *w, int *h);

	bool Collides(cRect *rc);
	bool CollidesMapWall(int *map, bool right);
	bool CollidesMapFloor(int *map);
	void GetArea(cRect *rc);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);
	bool insideWindow(Mapa map, int x, int y);
	bool MapCollides(Mapa map, int x, int y);

	void MoveRight(Mapa map);
	void MoveLeft(Mapa map);
	void MoveUp(Mapa map);
	void MoveDown(Mapa map);
	void Logic(Mapa map);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

private:
	int x, y;
	int w, h;
	int state;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq, delay;
};
