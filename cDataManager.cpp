#include "cDataManager.h"

cDataManager::cDataManager(void) {
	if (!userDataExists())
		prepareUserData();
}
cDataManager::~cDataManager(void) {}

bool cDataManager::userDataExists() {
	ifstream myfile("Save/user_data.txt");
	if (myfile.good()) {
		myfile.close();
		return true;
	}
	else {
		myfile.close();
		return false;
	}
}

bool cDataManager::prepareUserData() {
	bool res = true;
	ofstream myfile("Save/user_data.txt");
	if (myfile.is_open())
	{
		myfile << "high_score:0";
		myfile.close();
	}
	else {
		res = false;
	}
	return res;
}

int cDataManager::readMaxScore() {
	char highScore[32];

	ifstream file("Save/user_data.txt");
	string line[LINES_USER_DATA];
	int count = 0;
	while (getline(file, line[count]))
	{
		if (count == LINE_HIGH_SCORE) {
			int separatorPosition = line[count].find(":");
			string key = line[count].substr(0, separatorPosition);
			string value = line[count].substr(separatorPosition + 1, line[count].length());
			strcpy(highScore, value.c_str());
			break;
		}
		++count;
	}
	return atoi(highScore);
}

bool cDataManager::saveMaxScore(char* text) {
	bool res = true;

	ifstream file("Save/user_data.txt");
	string line[LINES_USER_DATA];
	int count = 0;
	while (getline(file, line[count]))
	{
		if (count == LINE_HIGH_SCORE) {
			int separatorPosition = line[count].find(":");
			string key = line[count].substr(0, separatorPosition);
			//string value = line[count].substr(separatorPosition+1, line[count].length());
			string value = text;
			line[count] = key + ":" + value;
		}
		++count;
	}

	ofstream myfile("Save/user_data.txt");
	if (myfile.is_open())
	{
		count = 0;
		while (count < LINES_USER_DATA) {
			myfile << line[count];
			++count;
		}
		myfile.close();
	}
	else {
		res = false;
	}

	return res;
}