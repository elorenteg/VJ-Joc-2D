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
	
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(0.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 50.0f, 25.0f, ABR_LEVEL_TEXT);
	
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(GAME_WIDTH - 100.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 50.0f, 25.0f, ABR_HEALTH_TEXT);
	
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(0.0f, 0.0f, GAMEINFO_DEPTH, 50.0f, 25.0f, ABR_SCORE_TEXT);
	
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(GAME_WIDTH - 100.0f, 0.0f, GAMEINFO_DEPTH, 70.0f, 25.0f, ABR_HIGH_SCORE_TEXT);

	glPopMatrix();
}