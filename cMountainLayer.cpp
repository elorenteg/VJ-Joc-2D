#include "cMountainLayer.h"
#include "Globals.h"

cMountainLayer::cMountainLayer(void) {}

cMountainLayer::~cMountainLayer(void) {}

bool cMountainLayer::LoadMountain() {
	bool res;

	res = true;

	id_DL = glGenLists(1);
	glNewList(id_DL, GL_COMPILE);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(0, 0, DEPTH);
	glTexCoord2f(10.0f, 1.0f); glVertex3i(GAME_WIDTH * 10, 0, DEPTH);
	glTexCoord2f(10.0f, 0.0f); glVertex3i(GAME_WIDTH * 10, GAME_HEIGHT / 2, DEPTH);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(0, GAME_HEIGHT / 2, DEPTH);
	glEnd();

	glEndList();

	return res;
}

void cMountainLayer::Draw(int tex_id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}

int* cMountainLayer::GetMap() {
	return map;
}
