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

	char scene_path[64];
	strcpy(scene_path, IMAGES_FOLDER);
	strcat(scene_path, "/");
	strcat(scene_path, "escena.png");
	res = Data.LoadImage(IMG_SCENE, scene_path, GL_RGBA);
	if (!res) return false;

	Font.setFont(Data.GetID(IMG_FONT), 256, 256, 19, 29);

	return res;
}

void cGameInfoLayer::Draw() {
	//glPushMatrix();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_SCENE));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.8f); glVertex3f(0, GAME_HEIGHT- GAME_MARGIN, SCENE_DEPTH);
		glTexCoord2f(9.0f, 0.8f); glVertex3f(GAME_WIDTH, GAME_HEIGHT - GAME_MARGIN, SCENE_DEPTH);
		glTexCoord2f(9.0f, 1.2f); glVertex3f(GAME_WIDTH, GAME_HEIGHT, SCENE_DEPTH);
		glTexCoord2f(0.0f, 1.2f); glVertex3f(0, GAME_HEIGHT, SCENE_DEPTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);

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
	
	//glPopMatrix();
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
