#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG			14

#define IMG_FONT		0
#define IMG_MARCO		1

#define IMG_BACKGROUND	2
#define IMG_LAYER2		3
#define IMG_SCENE		4

#define IMG_PLAYER		5
#define IMG_NINJA		6
#define IMG_GRADIENT	7
#define IMG_PIRATE		8
#define IMG_ZOMBIE		9

#define IMG_PROJ		10
#define IMG_PROJ_GRIS	11

#define IMG_RAINBOW		12

#define IMG_KEYBOARD	13

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img, int *w, int *h);
	bool LoadImage(int img, char *filename, int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
