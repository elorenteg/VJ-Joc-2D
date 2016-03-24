#pragma once

#include "cBicho.h"
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

private:
	int lifes = 3;
};
