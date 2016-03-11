#include "cSkyLayer.h"
#include "Globals.h"
#include <cmath>

cSkyLayer::cSkyLayer(void) {}

cSkyLayer::~cSkyLayer(void) {}

void cSkyLayer::Draw(int tex_id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glBegin(GL_QUADS);
	glTexCoord2f(texX, 1.0f); glVertex3i(0, 0, DEPTH);
	glTexCoord2f(texX + 1.0f, 1.0f); glVertex3i(GAME_WIDTH, 0, DEPTH);
	glTexCoord2f(texX + 1.0f, 0.0f); glVertex3i(GAME_WIDTH, GAME_HEIGHT, DEPTH);
	glTexCoord2f(texX, 0.0f); glVertex3i(0, GAME_HEIGHT, DEPTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	if (!isEndOfGame) texX = texX + 0.0002f * SPEED;
}

void cSkyLayer::endOfGame() {
	isEndOfGame = true;
}
