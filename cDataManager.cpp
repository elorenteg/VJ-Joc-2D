#include "cDataManager.h"

cDataManager::cDataManager(void) {}
cDataManager::~cDataManager(void) {}

char* cDataManager::readFile(char* file){
	return "hi";
}

bool cDataManager::saveFile(char* filename, char* content) {
	bool res = true;

	char path[128];
	strcpy(path, "Save/");
	strcat(path, filename);
	strcat(path, ".txt");

	ofstream myfile(path);
	if (myfile.is_open())
	{
		myfile << "This is a line.\n";
		myfile << content;
		myfile.close();
		OutputDebugStringA("File saved correctly \n");
	}
	else {
		OutputDebugStringA("Unable to open file \n");
		res = false;
	}

	return res;
}

char* cDataManager::readMaxScore() {
	return "hi";
}

bool cDataManager::saveMaxScore(char* text) {
	bool res = true;

	return res;
}