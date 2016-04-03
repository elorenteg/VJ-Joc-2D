#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG			24

#define IMG_FONT		0
#define IMG_MARCO		1

#define IMG_BACKGROUND	2
#define IMG_LAYER2		3
#define IMG_SCENE		4

#define IMG_WINGS		5
#define IMG_NINJA		6
#define IMG_GRADIENT	7
#define IMG_PIRATE		8
#define IMG_ZOMBIE		9
#define IMG_GAME_BOY	10
#define IMG_MEXICAN		11
#define IMG_OKTOBER		12
#define IMG_PIKACHU		13
#define IMG_TAC			14
#define IMG_MUMMY		15
#define IMG_GROUDON		16
#define IMG_PROJ		17
#define IMG_PROJ_NINJA	18
#define IMG_PROJ_PIRATE	19
#define IMG_PROJ_ZOMBIE	20

#define IMG_RAINBOW		21

#define IMG_KEYBOARD	22

#define IMG_HEART		23

#define NUMBER_OF_PLAYERS	5

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img, int *w, int *h);
	bool LoadImage(int img, char *filename, int type = GL_RGBA);

	int GetIMGPlayer(int pos);

	int playersArray[NUMBER_OF_PLAYERS] = { IMG_WINGS , IMG_GAME_BOY , IMG_MEXICAN , IMG_OKTOBER , IMG_PIKACHU };

private:
	cTexture texture[NUM_IMG];
};
