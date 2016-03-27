#pragma once

#include "cTexture.h"
#include "cScene.h"
#include "Globals.h"

#define BICHO_WIDTH		TILE_SIZE*3
#define BICHO_HEIGHT	TILE_SIZE*2

#define PROJ_WIDTH		TILE_SIZE*2
#define	PROJ_HEIGHT		TILE_SIZE/2

#define FRAME_DELAY		12
#define STEP_LENGTH		TILE_SIZE/4

#define MAX_FRAMES	5
#define FRAME_0		0
#define FRAME_1		1
#define FRAME_2		2
#define FRAME_3		3
#define FRAME_4		4

typedef struct Projectile {
	float x;
	float y;
	int state_color;
	int time_color;
};

class cRect
{
public:
	int left, top, right, bottom;
};

class cBicho
{
public:
	cBicho(void);
	cBicho(float x, float y, int w, int h);
	~cBicho(void);

	void SetPosition(float x, float y);
	void SetTile(int tx, int ty);
	void SetWidthHeight(int w, int h);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetXWindow(float xWindow);
	void SetMapValue(Matrix& map, int tile_x, int tile_y, int value);

	float GetX();
	float GetY();
	float GetXWindow();
	int GetWidth();
	int GetHeight();
	vector<Projectile> GetProjectiles();

	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);
	bool MapCollidesUp(Matrix& map, float step);
	bool MapCollidesDown(Matrix& map, float step);
	bool MapCollidesLeft(Matrix& map, float step);
	bool MapCollidesRight(Matrix& map, float step);

	void MoveRight(Matrix& map);
	void MoveLeft(Matrix& map);
	void MoveUp(Matrix& map);
	void MoveDown(Matrix& map);

	bool isEnemy(Matrix& map, int tile_x, int tile_y);
	virtual void HitEnemy();
	virtual void Shoot(Matrix& map);
	void DrawProjectiles(int tex_id);
	void MoveProjectiles(int dir);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

private:
	float x, y, z;
	int w, h;
	int state;
	float xWindow;

	vector<Projectile> projectiles;

	int seq, delay;
};
