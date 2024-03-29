#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
#include <string>
#include <iostream>
#include <vector>

#pragma warning(disable: 4996) // To supress _s warnings

using namespace std;

#define LEVELS_FOLDER	"Levels"
#define IMAGES_FOLDER	"Images"

#define TOTAL_LEVELS	3

#define GAME_WIDTH	640
#define GAME_HEIGHT	510
#define GAME_MARGIN	30
#define GAME_DEPTH	10

#define GAME_SCROLL 1.8f

#define SCENE_DEPTH		-6
#define MSS_DEPTH		0
#define GAMEINFO_DEPTH	-1

#define	GROUND			9
#define	GRASS			1
#define CLOUD_SUP_ESQ	2
#define CLOUD_SUP_CEN	3
#define CLOUD_SUP_DRE	4
#define CLOUD_INF_ESQ	5
#define CLOUD_INF_CEN	6
#define CLOUD_INF_DRE	7

#define	EMPTY			0

#define	RESERVED		'z'
#define PLAYER			'p'
#define ENEMY_VER		'v'
#define	ENEMY_HOR		'h'
#define ENEMY_CIR		'c'
#define BOSS			'b'

typedef vector<vector<int>> Matrix;

//OutputDebugStringA("HI");

//char msgbuf[128];
//strcpy(msgbuf, str_aux.c_str());
//OutputDebugStringA(msgbuf);

//char msgbuf[128];
//char aux_int[8];
//sprintf(aux_int, "%d", high_score);
//strcpy(msgbuf, aux_int);
//OutputDebugStringA(msgbuf);