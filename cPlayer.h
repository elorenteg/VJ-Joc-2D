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

	void Reset();
	void ResetLife();

	int GetScore();
	void SetLifes(int new_life);
	int GetLifes();

	void Draw(int tex_id);
	void DrawRainbow(int tex_id, float xWindow);

	bool isOutsideWindow();
	bool isGameOver();
	
	void Logic(Matrix& map, float cameraXScene);
	void HitEnemy();
	Projectile InitShoot();

	void LogicProjectiles(Matrix& map, vector<cEnemyVertical>& vers, vector<cEnemyHorizontal>& hors, vector<cEnemyCircle>& cirs);

private:
	int lifes;
	int score;

	void HitProjectile(Matrix& map, vector<cEnemyVertical>& vers);
	void HitProjectile(Matrix& map, vector<cEnemyHorizontal>& vers);
	void HitProjectile(Matrix& map, vector<cEnemyCircle>& vers);
};
