#include "cMountainLayer.h"

cMountainLayer::cMountainLayer(void) {}

cMountainLayer::~cMountainLayer(void) {}

void cMountainLayer::Draw(int tex_id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glColor3f(0.6f, 0.6f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(texX, 1.0f); glVertex3i(0, 0, DEPTH);
	glTexCoord2f(texX + 1.0f, 1.0f); glVertex3i(GAME_WIDTH, 0, DEPTH);
	glTexCoord2f(texX + 1.0f, 0.0f); glVertex3i(GAME_WIDTH, GAME_HEIGHT/2, DEPTH);
	glTexCoord2f(texX, 0.0f); glVertex3i(0, GAME_HEIGHT/2, DEPTH);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	glDisable(GL_TEXTURE_2D);

	if (!isEndOfGame) texX += GAME_SCROLL * SPEED;
}

void cMountainLayer::endOfGame() {
	isEndOfGame = true;
}