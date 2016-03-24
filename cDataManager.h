#pragma once

#include <fstream>
#include "Globals.h"

#define LINES_USER_DATA		1
#define LINE_HIGH_SCORE		0

class cDataManager
{
public:
	cDataManager(void);
	~cDataManager(void);

	bool prepareUserData();
	char* readMaxScore();
	bool saveMaxScore(char* text);

private:

};
