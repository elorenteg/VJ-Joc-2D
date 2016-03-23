#pragma once

#include <fstream>
#include "Globals.h"


class cDataManager
{
public:
	cDataManager(void);
	~cDataManager(void);

	char* readFile(char* file);
	bool saveFile(char* filename, char* content);

	char* readMaxScore();
	bool saveMaxScore(char* text);

private:

};
