#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG			12

#define IMG_FONT		0
#define IMG_MARCO		1

#define IMG_BACKGROUND	2
#define IMG_LAYER2		3
#define IMG_SCENE		4

#define IMG_PLAYER		5
#define IMG_NINJA		6
#define IMG_GRADIENT	7

#define IMG_PROJ		8
#define IMG_PROJ_GRIS	9

#define IMG_RAINBOW		10

#define IMG_KEYBOARD	11


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
