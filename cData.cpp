#include "cData.h"

cData::cData(void) {
	
}
cData::~cData(void) {}

int cData::GetID(int img)
{
	return texture[img].GetID();
}

void cData::GetSize(int img, int *w, int *h)
{
	texture[img].GetSize(w, h);
}

bool cData::LoadImage(int img, char *filename, int type)
{
	int res = texture[img].Load(filename, type);
	if (!res) return false;

	return true;
}

int cData::GetIMGPlayer(int pos) {
	return playersArray[pos];
}