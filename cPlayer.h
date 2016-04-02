#pragma once

#include "cBicho.h"
#include "cEnemyVertical.h"
#include "cEnemyHorizontal.h"
#include "cEnemyCircle.h"
#include "Globals.h"

#define SIZE_RAINBOW	3

typedef struct Position {
	float x;
	float y;
};

class cPlayer : public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Reset();
	void ResetLife();

	void Draw(int tex_id);
	void DrawRainbow(int tex_id, float xWindow);

	bool isOutsideWindow();
	bool isGameOver();
	bool canMove(Matrix& map, int tx, int ty);
	
	void Logic(Matrix& map, float cameraXScene);
	Projectile InitShoot();

private:
	int state_rainbow;
	vector<Position> Rainbow;
};
