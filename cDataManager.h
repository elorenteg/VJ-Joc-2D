#pragma once

#include <fstream>
#include "cData.h"
#include "Globals.h"

#define LINES_USER_DATA		2
#define LINE_HIGH_SCORE		0
#define LINE_PLAYER			1

class cDataManager
{
public:
	cDataManager(void);
	~cDataManager(void);

	bool userDataExists();
	bool prepareUserData();

	int readPlayerIcon();
	bool savePlayerIcon(int icon);

	int readMaxScore();
	bool saveMaxScore(char* text);

private:

};
