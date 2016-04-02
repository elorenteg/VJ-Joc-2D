#include "cMountainLayer.h"

cMountainLayer::cMountainLayer(void) {}

cMountainLayer::~cMountainLayer(void) {}

void cMountainLayer::Draw(int tex_id, int level) {
	float yo, yf;
	if (level == 1) {
		yf = 0.0f;
		yo = 1.0f / 3;
	}
	else if (level == 2) {
		yf = 1.0f / 3;
		yo = 2* 1.0f / 3;
	}
	else {
		yf = 2 * 1.0f / 3;
		yo = 1.0f;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glColor3f(0.9f, 0.9f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(texX, yo); glVertex3i(0, 0, DEPTH);
	glTexCoord2f(texX + 1.0f, yo); glVertex3i(GAME_WIDTH, 0, DEPTH);
	glTexCoord2f(texX + 1.0f, yf); glVertex3i(GAME_WIDTH, GAME_HEIGHT/2, DEPTH);
	glTexCoord2f(texX, yf); glVertex3i(0, GAME_HEIGHT/2, DEPTH);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	glDisable(GL_TEXTURE_2D);

	if (!isEndOfLevel) texX += GAME_SCROLL * SPEED;
}

void cMountainLayer::endOfLevel() {
	isEndOfLevel = true;
}

void cMountainLayer::restartLevel() {
	isEndOfLevel = false;
}