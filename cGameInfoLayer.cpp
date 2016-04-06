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

	char heart_path[64];
	strcpy(heart_path, IMAGES_FOLDER);
	strcat(heart_path, "/");
	strcat(heart_path, "heart.png");
	res = Data.LoadImage(IMG_HEART, heart_path, GL_RGBA);
	if (!res) return false;

	Font.setFont(Data.GetID(IMG_FONT), 256, 256, 19, 29);

	current_level = 1;
	high_score = DataManager.readMaxScore();
	current_score = 0;
	current_life = 3;
	showBossLife = false;

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
	glColor3f(0.1f, 0.1f, 0.1f);
	char level_text[32];
	strcpy(level_text, ABR_LEVEL_TEXT);
	strcat(level_text, ": ");
	char level_value[8];
	sprintf(level_value, "%d", current_level);
	strcat(level_text, level_value);
	Font.drawText(5.0f, GAME_HEIGHT - 22.0f, GAMEINFO_DEPTH, 90.0f, 20.0f, level_text);

	// Vides
	glColor3f(0.1f, 0.1f, 0.1f);
	char life_text[32];
	strcpy(life_text, ABR_HEALTH_TEXT);
	strcat(life_text, ": ");
	//char life_value[8];
	//sprintf(life_value, "%d", current_life);
	//strcat(life_text, life_value);
	Font.drawText(130.0f, GAME_HEIGHT - 22.0f, GAMEINFO_DEPTH, 75.0f, 20.0f, life_text);

	glColor3f(1.0f, 1.0f, 1.0f);
	if (current_life > 0) {
		drawImage(Data.GetID(IMG_HEART), 210.0f, GAME_HEIGHT - 20.0f, GAMEINFO_DEPTH, 20.0f, 16.0f);
	}
	if (current_life > 1) {
		drawImage(Data.GetID(IMG_HEART), 232.0f, GAME_HEIGHT - 20.0f, GAMEINFO_DEPTH, 20.0f, 16.0f);
	}
	if (current_life > 2) {
		drawImage(Data.GetID(IMG_HEART), 254.0f, GAME_HEIGHT - 20.0f, GAMEINFO_DEPTH, 20.0f, 16.0f);
	}

	// Puntuacio
	glColor3f(0.1f, 0.1f, 0.1f);
	char score_text[32];
	strcpy(score_text, ABR_SCORE_TEXT);
	strcat(score_text, ": ");
	char score_value[8];
	sprintf(score_value, "%d", current_score);
	strcat(score_text, score_value);
	Font.drawText(GAME_WIDTH - 300.0f, GAME_HEIGHT - 22.0f, GAMEINFO_DEPTH, 135.0f, 20.0f, score_text);

	// Maxima Puntuacio
	glColor3f(0.1f, 0.1f, 0.1f);
	char high_score_text[32];
	strcpy(high_score_text, ABR_HIGH_SCORE_TEXT);
	strcat(high_score_text, ": ");
	char high_score_value[8];
	sprintf(high_score_value, "%d", high_score);
	strcat(high_score_text, high_score_value);
	Font.drawText(GAME_WIDTH - 140.0f, GAME_HEIGHT - 22.0f, GAMEINFO_DEPTH, 120.0f, 20.0f, high_score_text);

	// Vida del Boss
	if (showBossLife) {
		int w = 150;
		float xo = GAME_WIDTH - w - 7;
		int max_life = 30 / (TOTAL_LEVELS - current_level + 1);
		float xm = (double(current_life_boss) / max_life)*w;
		float yo = 7;

		glColor3f(0.0f, 1.0f, 0.0f);
		drawRectangle(xo, yo, GAMEINFO_DEPTH, xm, 18);
		glColor3f(0.0f, 0.0f, 0.0f);
		drawRectangle(xo + xm, yo, GAMEINFO_DEPTH, w - xm, 18);

		glColor3f(0.1f, 0.1f, 0.1f);
		char boss_health_text[32];
		strcpy(boss_health_text, ABR_HEALTH_BOSS_TEXT);
		strcat(boss_health_text, ": ");
		Font.drawText(xo - 120.0f, yo - 1, GAMEINFO_DEPTH, 120.0f, 20.0f, boss_health_text);
	}
}

void cGameInfoLayer::SetCurrentLevel(int level) {
	current_level = level;
}

int cGameInfoLayer::GetCurrentLevel() {
	return current_level;
}

void cGameInfoLayer::SetHighScore(int score) {
	high_score = score;

	SaveHighScore(high_score);
}

int cGameInfoLayer::GetHighScore() {
	return high_score;
}

void cGameInfoLayer::SetCurrentScore(int score) {
	current_score = score;

	if (current_score > high_score) {
		high_score = current_score;

		SaveHighScore(high_score);
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

void cGameInfoLayer::SetCurrentLifeBoss(int life) {
	current_life_boss = life;
}

int cGameInfoLayer::GetCurrentLifeBoss() {
	return current_life_boss;
}

void cGameInfoLayer::SetShowBossLife(bool show) {
	showBossLife = show;
}

void cGameInfoLayer::SaveHighScore(int high_score) {
	char high_score_value[8];
	sprintf(high_score_value, "%d", high_score);
	DataManager.saveMaxScore(high_score_value);
}

void cGameInfoLayer::drawImage(int tex_id, float x, float y, float z, float w, float h) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(x + w, y, z);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(x + w, y + h, z);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y + h, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
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
