#include "cGameInfoLayer.h"

cGameInfoLayer::cGameInfoLayer(void) {}

cGameInfoLayer::~cGameInfoLayer(void) {}

bool cGameInfoLayer::Init() {
	bool res = true;
	char font_path[64];
	strcpy(font_path, IMAGES_FOLDER);
	strcat(font_path, "/");
	strcat(font_path, "font.png");
	res = Data.LoadImage(IMG_FONT, font_path, GL_RGBA);
	if (!res) return false;

	Font.setFont(Data.GetID(IMG_FONT), 256, 256, 19, 29);

	return res;
}

void cGameInfoLayer::Draw() {
	glPushMatrix();
	
	//glColor3f(1.0f, 1.0f, 0.0f);
	//drawRectangle(0.0f, GAME_HEIGHT - 25, -2.0f, GAME_WIDTH, 25.0f);

	// Nivell
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(0.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 90.0f, 25.0f, ABR_LEVEL_TEXT);
	
	// Vides
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(125.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 75.0f, 25.0f, ABR_HEALTH_TEXT);
	
	// Puntuacio
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(GAME_WIDTH - 350.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 135.0f, 25.0f, ABR_SCORE_TEXT);
	
	// Maxima Puntuacio
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(GAME_WIDTH - 175.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 135.0f, 25.0f, ABR_HIGH_SCORE_TEXT);
	
	glPopMatrix();
}

// Draw the rectangle
void cGameInfoLayer::drawRectangle(float x, float y, float z, float width, float height) {
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x, y + height, z);
	glEnd();
}
