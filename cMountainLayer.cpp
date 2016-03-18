#include "cMountainLayer.h"

cMountainLayer::cMountainLayer(void) {}

cMountainLayer::~cMountainLayer(void) {}

void cMountainLayer::Draw(int tex_id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glBegin(GL_QUADS);
	glTexCoord2f(texX, 1.0f); glVertex3i(0, 0, DEPTH);
	glTexCoord2f(texX + 1.0f, 1.0f); glVertex3i(GAME_WIDTH, 0, DEPTH);
	glTexCoord2f(texX + 1.0f, 0.0f); glVertex3i(GAME_WIDTH, GAME_HEIGHT/2, DEPTH);
	glTexCoord2f(texX, 0.0f); glVertex3i(0, GAME_HEIGHT/2, DEPTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	if (!isEndOfGame) texX = texX + 0.0002f * SPEED;
}

void cMountainLayer::endOfGame() {
	isEndOfGame = true;
}