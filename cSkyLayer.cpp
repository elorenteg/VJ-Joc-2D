#include "cSkyLayer.h"

cSkyLayer::cSkyLayer(void) {}

cSkyLayer::~cSkyLayer(void) {}

void cSkyLayer::Draw(int tex_id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glBegin(GL_QUADS);
		glColor3f(0.5f, 0.5f, 0.8f);
		glTexCoord2f(texX, 1.0f); glVertex3i(0, 0, DEPTH);
		glTexCoord2f(texX + 1.0f, 1.0f); glVertex3i(GAME_WIDTH, 0, DEPTH);

		glColor3f(0.2f, 0.2f, 0.5f);
		glTexCoord2f(texX + 1.0f, 0.0f); glVertex3i(GAME_WIDTH, GAME_HEIGHT, DEPTH);
		glTexCoord2f(texX, 0.0f); glVertex3i(0, GAME_HEIGHT, DEPTH);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	glDisable(GL_TEXTURE_2D);

	if (!isEndOfGame) texX += GAME_SCROLL * SPEED;
}

void cSkyLayer::endOfGame() {
	isEndOfGame = true;
}
