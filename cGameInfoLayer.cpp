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

	current_level = 1;
	high_score = DataManager.readMaxScore();
	current_score = 0;
	current_life = 3;

	return res;
}

void cGameInfoLayer::Draw() {
	// Background
	glColor3f(0.9f, 0.9f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_SCENE));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.8f); glVertex3f(0, GAME_HEIGHT - GAME_MARGIN, SCENE_DEPTH);
	glTexCoord2f(9.0f, 0.8f); glVertex3f(GAME_WIDTH, GAME_HEIGHT - GAME_MARGIN, SCENE_DEPTH);
	glTexCoord2f(9.0f, 1.2f); glVertex3f(GAME_WIDTH, GAME_HEIGHT, SCENE_DEPTH);
	glTexCoord2f(0.0f, 1.2f); glVertex3f(0, GAME_HEIGHT, SCENE_DEPTH);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// Nivell
	glColor3f(0.0f, 0.0f, 0.0f);
	char level_text[32];
	strcpy(level_text, ABR_LEVEL_TEXT);
	strcat(level_text, ": ");
	char level_value[8];
	sprintf(level_value, "%d", current_level);
	strcat(level_text, level_value);
	Font.drawText(5.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 90.0f, 25.0f, level_text);

	// Vides
	glColor3f(0.0f, 0.0f, 0.0f);
	char life_text[32];
	strcpy(life_text, ABR_HEALTH_TEXT);
	strcat(life_text, ": ");
	char life_value[8];
	sprintf(life_value, "%d", current_life);
	strcat(life_text, life_value);
	Font.drawText(110.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 75.0f, 25.0f, life_text);

	// Puntuacio
	glColor3f(0.0f, 0.0f, 0.0f);
	char score_text[32];
	strcpy(score_text, ABR_SCORE_TEXT);
	strcat(score_text, ": ");
	char score_value[8];
	sprintf(score_value, "%d", current_score);
	strcat(score_text, score_value);
	Font.drawText(GAME_WIDTH - 275.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 135.0f, 25.0f, score_text);

	// Maxima Puntuacio
	glColor3f(0.0f, 0.0f, 0.0f);
	char high_score_text[32];
	strcpy(high_score_text, ABR_HIGH_SCORE_TEXT);
	strcat(high_score_text, ": ");
	char high_score_value[8];
	sprintf(high_score_value, "%d", high_score);
	strcat(high_score_text, high_score_value);
	Font.drawText(GAME_WIDTH - 125.0f, GAME_HEIGHT - 25.0f, GAMEINFO_DEPTH, 120.0f, 25.0f, high_score_text);
}

void cGameInfoLayer::SetCurrentLevel(int level) {
	current_level = level;
}

int cGameInfoLayer::GetCurrentLevel() {
	return current_level;
}

int cGameInfoLayer::GetHighScore() {
	return high_score;
}

void cGameInfoLayer::SetCurrentScore(int score) {
	current_score = score;

	if (current_score > high_score) {
		high_score = current_score;

		char high_score_value[8];
		sprintf(high_score_value, "%d", high_score);
		DataManager.saveMaxScore(high_score_value);

		char msgbuf[128];
		strcpy(msgbuf, "GUARDANDO: ");
		strcat(msgbuf, high_score_value);
		OutputDebugStringA(msgbuf);
	}
}

int cGameInfoLayer::GetCurrentScore() {
	return current_score;
}

void cGameInfoLayer::SetCurrentLife(int life) {
	current_life = life;
}

int cGameInfoLayer::GetCurrentLife() {
	return current_life;
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
