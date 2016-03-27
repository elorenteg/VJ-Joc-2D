#pragma once

#include "cBicho.h"
#include "cEnemyVertical.h"
#include "cEnemyHorizontal.h"
#include "cEnemyCircle.h"
#include "Globals.h"

class cPlayer : public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);
	void DrawRainbow(int tex_id, float xWindow);
	bool isGameOver();
	
	void Logic(Matrix& map, float cameraXScene);
	void HitEnemy();
	void LogicProjectiles(Matrix& map, vector<cEnemyVertical>& vers, vector<cEnemyHorizontal>& hors, vector<cEnemyCircle>& cirs);
	void HitProjectile(Matrix& map, vector<cEnemyVertical>& vers);

private:
	int lifes = 3;
};
