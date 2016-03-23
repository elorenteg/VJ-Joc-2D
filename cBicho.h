#pragma once

#include "cTexture.h"
#include "cScene.h"
#include "Globals.h"

#define FRAME_DELAY		12
#define STEP_LENGTH		4

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
	cBicho(float x, float y, int w, int h);
	~cBicho(void);

	void SetPosition(float x, float y);
	void SetTile(int tx, int ty);
	void SetWidthHeight(int w, int h);

	float GetX();
	float GetY();
	float GetXWindow();
	int GetWidth();
	int GetHeight();

	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);
	bool MapCollidesUp(Matrix& map, float x, float y);
	bool MapCollidesDown(Matrix& map, float x, float y);
	bool MapCollidesLeft(Matrix& map, float x, float y);
	bool MapCollidesRight(Matrix& map, float x, float y);

	void MoveRight(Matrix& map);
	void MoveLeft(Matrix& map);
	void MoveUp(Matrix& map);
	void MoveDown(Matrix& map);
	void Logic(Matrix& map, float cameraXScene);

	virtual void HitEnemy();

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

private:
	float x, y;
	int w, h;
	int state;
	float xWindow;

	int seq, delay;
};
