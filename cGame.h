#pragma once

#include "cScene.h"
#include "cSkyLayer.h"
#include "cMountainLayer.h"
#include "cPlayer.h"
#include "cData.h"
#include "Globals.h"

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);

	//Process
	bool Process();

	//Output
	void Render();
	void UpdateCameraScene();
	void RestartCameraScene();

private:
	unsigned char keys[256];
	cSkyLayer SkyLayer;
	cMountainLayer MountainLayer;
	cScene Scene;
	cPlayer Player;
	cData Data;

	float cameraXScene;
};
