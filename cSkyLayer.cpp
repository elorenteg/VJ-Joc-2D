#include "cSkyLayer.h"

cSkyLayer::cSkyLayer(void) {}

cSkyLayer::~cSkyLayer(void) {}

void cSkyLayer::Draw(int tex_id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
		//glColor3f(0.7f, 0.7f, 1.0f);
		glTexCoord2f(texX, 1.0f); glVertex3i(0, 0, DEPTH);
		glTexCoord2f(texX + 1.0f, 1.0f); glVertex3i(GAME_WIDTH, 0, DEPTH);

		//glColor3f(0.4f, 0.4f, 1.0f);
		glTexCoord2f(texX + 1.0f, 0.0f); glVertex3i(GAME_WIDTH, GAME_HEIGHT, DEPTH);
		glTexCoord2f(texX, 0.0f); glVertex3i(0, GAME_HEIGHT, DEPTH);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	glDisable(GL_TEXTURE_2D);

	if (!isEndOfLevel) texX += GAME_SCROLL * SPEED;
}

void cSkyLayer::endOfLevel() {
	isEndOfLevel = true;
}

void cSkyLayer::restartLevel() {
	isEndOfLevel = false;
}