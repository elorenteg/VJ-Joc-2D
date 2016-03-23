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

#define GAME_WIDTH	640
#define GAME_HEIGHT 480
#define GAME_DEPTH	10

#define GAME_SCROLL 1.2f

#define SCENE_DEPTH		-6
#define MSS_DEPTH		0
#define GAMEINFO_DEPTH	-1

typedef vector<vector<int>> Matrix;

//OutputDebugStringA("HI");
