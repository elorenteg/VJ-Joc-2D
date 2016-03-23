#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG			8

#define IMG_FONT		0
#define IMG_MARCO		1

#define IMG_BACKGROUND	2
#define IMG_LAYER2		3
#define IMG_SCENE		4

#define IMG_PLAYER		5
#define IMG_ENEMY		6
#define IMG_SHOOT		7


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
