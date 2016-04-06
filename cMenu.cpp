#include "cMenu.h"
#include "cPlayer.h"

cPlayer Player;

cMenu::cMenu(void)
{
	starsX = vector<float>(maxStars);
	starsY = vector<float>(maxStars);
}

cMenu::~cMenu(void)
{
}

bool cMenu::Init()
{
	bool res = true;
	actionSelected = gameAction;
	processingKey = false;
	currentState = MENU;
	internalState = MENU;

	//Graphics initialization
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	char font_path[64];
	strcpy(font_path, IMAGES_FOLDER);
	strcat(font_path, "/");
	strcat(font_path, "font.png");
	res = Data.LoadImage(IMG_FONT, font_path, GL_RGBA);
	if (!res) return false;

	char player_path_1[64];
	strcpy(player_path_1, IMAGES_FOLDER);
	strcat(player_path_1, "/");
	strcat(player_path_1, "nyancat_player_wings.png");
	res = Data.LoadImage(IMG_WINGS, player_path_1, GL_RGBA);
	if (!res) return false;

	char player_path_2[64];
	strcpy(player_path_2, IMAGES_FOLDER);
	strcat(player_path_2, "/");
	strcat(player_path_2, "nyancat_player_game_boy.png");
	res = Data.LoadImage(IMG_GAME_BOY, player_path_2, GL_RGBA);
	if (!res) return false;

	char player_path_3[64];
	strcpy(player_path_3, IMAGES_FOLDER);
	strcat(player_path_3, "/");
	strcat(player_path_3, "nyancat_player_mexican.png");
	res = Data.LoadImage(IMG_MEXICAN, player_path_3, GL_RGBA);
	if (!res) return false;

	char player_path_4[64];
	strcpy(player_path_4, IMAGES_FOLDER);
	strcat(player_path_4, "/");
	strcat(player_path_4, "nyancat_player_oktober.png");
	res = Data.LoadImage(IMG_OKTOBER, player_path_4, GL_RGBA);
	if (!res) return false;

	char player_path_5[64];
	strcpy(player_path_5, IMAGES_FOLDER);
	strcat(player_path_5, "/");
	strcat(player_path_5, "nyancat_player_picachu.png");
	res = Data.LoadImage(IMG_PIKACHU, player_path_5, GL_RGBA);
	if (!res) return false;

	char keyboard_arrow_path[64];
	strcpy(keyboard_arrow_path, IMAGES_FOLDER);
	strcat(keyboard_arrow_path, "/");
	strcat(keyboard_arrow_path, "keyboard_arrows.png");
	res = Data.LoadImage(IMG_KEYBOARD, keyboard_arrow_path, GL_RGBA);
	if (!res) return false;

	currentPlayerIDPos = DataManager.readPlayerIcon();

	Font.setFont(Data.GetID(IMG_FONT), 256, 256, 19, 29);
	calculate_stars();

	return res;
}

bool cMenu::Loop()
{
	bool res = true;

	res = Process();
	if (res) Render();

	next_game_tick = GetTickCount() + SKIP_TICKS;
	sleep_time = next_game_tick - GetTickCount();
	if (sleep_time >= 0) {
		Sleep(sleep_time);
	}

	--time_same_stars;
	if (time_same_stars == 0) {
		time_same_stars = 5;
		calculate_stars();
	}

	return res;
}

void cMenu::Finalize()
{
}

//Input
void cMenu::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;

	processingKey = press;
}

void cMenu::ReadMouse(int button, int state, int x, int y)
{

}

//Process
bool cMenu::Process()
{
	bool res = true;

	if (processingKey) {
		processingKey = false;

		//Process Input
		if (keys[27]) { //ESC
			switch (internalState) {
			case MENU:
				res = false;
				break;
			case HOW_TO:
				internalState = MENU;
				page = PAGE_1;
				break;
			case OPTIONS:
				internalState = MENU;
				page = PAGE_1;
				break;
			case CREDITS:
				internalState = MENU;
				page = PAGE_1;
				break;
			}
		}
		else if (keys[GLUT_KEY_UP]) {
			if (internalState != HOW_TO)
				moveAction(-1);
		}
		else if (keys[GLUT_KEY_DOWN]) {
			if (internalState != HOW_TO)
				moveAction(1);
		}
		else if (keys[GLUT_KEY_LEFT]) {
			if (internalState == HOW_TO) {
				if (page == PAGE_2) {
					page = PAGE_1;
				}
			}
		}
		else if (keys[GLUT_KEY_RIGHT]) {
			if (internalState == HOW_TO) {
				if (page == PAGE_1) {
					page = PAGE_2;
				}
			}
		}
		else if (keys[13]) { //Enter
			keys[13] = false;
			if (internalState != HOW_TO)
				executeAction();
		}

		if (internalState == OPTIONS) {
			if (keys[GLUT_KEY_LEFT]) {
				if (currentPlayerIDPos > 0) {
					currentPlayerIDPos--;
					DataManager.savePlayerIcon(currentPlayerIDPos);
				}
			}
			else if (keys[GLUT_KEY_RIGHT]) {
				if (currentPlayerIDPos < NUMBER_OF_PLAYERS - 1) {
					currentPlayerIDPos++;
					DataManager.savePlayerIcon(currentPlayerIDPos);
				}
			}
		}
	}

	return res;
}

//Output
void cMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
	glLoadIdentity();

	render_stars();

	switch (internalState) {
	case MENU:
		showMenu();
		break;
	case HOW_TO:
		showInstrucctions();
		break;
	case OPTIONS:
		showOptions();
		break;
	case CREDITS:
		showCredits();
		break;
	}

	glutSwapBuffers();
}

//State in use
void cMenu::SetState(int state) {
	currentState = state;
}

int cMenu::GetState() {
	return currentState;
}

void cMenu::executeAction() {
	if (actionSelected == gameAction) {
		currentState = START_GAME;
	}
	else if (actionSelected == howtoAction) {
		page = PAGE_1;
		internalState = HOW_TO;
	}
	else if (actionSelected == optionsAction) {
		page = PAGE_1;
		internalState = OPTIONS;
	}
	else if (actionSelected == creditsAction) {
		page = PAGE_1;
		internalState = CREDITS;
	}
	else if (actionSelected == stopAction) {
		exit(0);
	}
}

void cMenu::moveAction(int moveTo) {
	if (actionSelected == gameAction) {
		if (moveTo == 1) {
			actionSelected = howtoAction;
			Sound.PlayCustomSound(CHANGE_IN_MENU);
		}
	}
	else if (actionSelected == howtoAction) {
		if (moveTo == 1) {
			actionSelected = optionsAction;
			Sound.PlayCustomSound(CHANGE_IN_MENU);
		}
		else if (moveTo == -1) {
			actionSelected = gameAction;
			Sound.PlayCustomSound(CHANGE_IN_MENU);
		}
	}
	else if (actionSelected == optionsAction) {
		if (moveTo == 1) {
			actionSelected = creditsAction;
			Sound.PlayCustomSound(CHANGE_IN_MENU);
		}
		else if (moveTo == -1) {
			actionSelected = howtoAction;
			Sound.PlayCustomSound(CHANGE_IN_MENU);
		}
	}
	else if (actionSelected == creditsAction) {
		if (moveTo == 1) {
			//actionSelected = stopAction;
			//Sound.PlayCustomSound(CHANGE_IN_MENU);
		}
		else if (moveTo == -1) {
			actionSelected = optionsAction;
			Sound.PlayCustomSound(CHANGE_IN_MENU);
		}
	}
	else if (actionSelected == stopAction) {
		if (moveTo == -1) {
			actionSelected = creditsAction;
			Sound.PlayCustomSound(CHANGE_IN_MENU);
		}
	}
}

void cMenu::showMenu() {
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 105.0f, GAME_HEIGHT / 2.0f + 130.0f, MSS_DEPTH, 200.0f, 50.0f, PLAY_TEXT);

	Font.drawText(GAME_WIDTH / 2.0f - 100.0f, GAME_HEIGHT / 2.0f + 30.0f, MSS_DEPTH, 200.0f, 50.0f, HOW_TO_TEXT);

	Font.drawText(GAME_WIDTH / 2.0f - 100.0f, GAME_HEIGHT / 2.0f - 70.0f, MSS_DEPTH, 200.0f, 50.0f, OPTIONS_TEXT);

	Font.drawText(GAME_WIDTH / 2.0f - 105.0f, GAME_HEIGHT / 2.0f - 170.0f, MSS_DEPTH, 200.0f, 50.0f, CREDITS_TEXT);
	
	Font.drawText(GAME_WIDTH - 200.0f, 20.0f, MSS_DEPTH, 175.0f, 20.0f, EXIT_HOW_TEXT);
	
	glPopMatrix();

	if (actionSelected == gameAction)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.5f, 0.5f, 0.5f);
	drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f + 115.0f, MSS_DEPTH - 1, 300.0f, 75.0f);

	if (actionSelected == howtoAction)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(0.5f, 0.5f, 0.5f);
	drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f + 15.0f, MSS_DEPTH - 1, 300.0f, 75.0f);

	if (actionSelected == optionsAction)
		glColor3f(1.0f, 1.0f, 0.0f);
	else
		glColor3f(0.5f, 0.5f, 0.5f);
	drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f - 85.0f, MSS_DEPTH - 1, 300.0f, 75.0f);

	if (actionSelected == creditsAction)
		glColor3f(0.0f, 0.0f, 1.0f);
	else
		glColor3f(0.5f, 0.5f, 0.5f);
	drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f - 185.0f, MSS_DEPTH - 1, 300.0f, 75.0f);
}

void cMenu::showInstrucctions() {
	glPushMatrix();

	//Instruccions titol
	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 160.0f, GAME_HEIGHT / 2.0f + 160.0f, MSS_DEPTH - 1, 300.0f, 40.0f, HOW_TO_TEXT);

	if (page == PAGE_1) {
		//Explicacio 1
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(65.0f, GAME_HEIGHT - 165.0f, MSS_DEPTH - 1, 350.0f, 20.0f, HOW_TO_PLAYER_TEXT_1_1);

		//Nyan Image
		glColor3f(1.0f, 1.0f, 1.0f);
		Player.SetPosition(GAME_WIDTH / 2.0f - 40.0f, GAME_HEIGHT - 235.0f);
		setPlayerSize();
		Player.SetZ(MSS_DEPTH - 1);
		Player.Draw(Data.GetID(Data.GetIMGPlayer(currentPlayerIDPos)));

		//Explicacio 2
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(65.0f, GAME_HEIGHT - 300.0f, MSS_DEPTH - 1, 500.0f, 20.0f, HOW_TO_PLAYER_TEXT_1_2);

		//Keyboard Image
		glColor3f(1.0f, 1.0f, 1.0f);
		drawImage(Data.GetID(IMG_KEYBOARD), GAME_WIDTH / 2.0f - 105.0f, 60.0f, MSS_DEPTH - 1, 200.0f, 120.0f);
	}
	else if (page == 2) {
		//Explicacio 1
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(65.0f, GAME_HEIGHT - 165.0f, MSS_DEPTH - 1, 350.0f, 20.0f, HOW_TO_PLAYER_TEXT_2_1);

		//Explicacio 2
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(64.0f, GAME_HEIGHT - 200.0f, MSS_DEPTH - 1, 350.0f, 20.0f, HOW_TO_PLAYER_TEXT_2_2);
	}
	//Fons
	glColor3f(0.8f, 0.8f, 0.85f);
	drawRectangle(50.0f, 50.0f, MSS_DEPTH - 2, GAME_WIDTH - 100.0f, GAME_HEIGHT - 180.0f);

	glPopMatrix();
}

void cMenu::showOptions() {
	glPushMatrix();

	//Opcions titol
	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 105.0f, GAME_HEIGHT / 2.0f + 160.0f, MSS_DEPTH, 200.0f, 40.0f, OPTIONS_TEXT);

	//HighScore Part
	glColor3f(0.0f, 0.0f, 0.0f);
	char high_score_text[32];
	strcpy(high_score_text, OPTIONS_HIGH_SCORE);
	char high_score_value[8];
	int high_score = DataManager.readMaxScore();
	sprintf(high_score_value, "%d", high_score);
	strcat(high_score_text, high_score_value);
	Font.drawText(75.0f, GAME_HEIGHT - 210.0f, MSS_DEPTH - 1, 200.0f, 20.0f, high_score_text);

	//Fons
	glColor3f(0.0f, 0.8f, 0.85f);
	drawRectangle(50.0f, GAME_HEIGHT - 250.0f, MSS_DEPTH - 2, GAME_WIDTH - 100.0f, 100.0f);

	//Seleccio personatge
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(75.0f, GAME_HEIGHT - 375.0f, MSS_DEPTH - 1, 250.0f, 20.0f, OPTIONS_SELECCIO_PLAYER);

	Font.drawText(GAME_WIDTH / 2.0f + 5.0f, GAME_HEIGHT - 385.0f, MSS_DEPTH - 1, 30.0f, 50.0f, "<");
	Font.drawText(GAME_WIDTH / 2.0f + 105.0f, GAME_HEIGHT - 385.0f, MSS_DEPTH - 1, 30.0f, 50.0f, ">");
	glColor3f(1.0f, 1.0f, 1.0f);
	Player.SetPosition(GAME_WIDTH / 2.0f + 40.0f, GAME_HEIGHT - 380.0f);
	setPlayerSize();
	Player.SetZ(MSS_DEPTH - 1);
	Player.Draw(Data.GetID(Data.GetIMGPlayer(currentPlayerIDPos)));

	//Fons
	glColor3f(0.8f, 0.8f, 0.85f);
	drawRectangle(50.0f, 100.0f, MSS_DEPTH - 2, GAME_WIDTH - 100.0f, 100.0f);

	glPopMatrix();
}

void cMenu::showCredits() {
	glPushMatrix();

	//Credits titol
	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 105.0f, GAME_HEIGHT / 2.0f + 160.0f, MSS_DEPTH, 200.0f, 40.0f, CREDITS_TEXT);

	//Nyan Image
	glColor3f(1.0f, 1.0f, 1.0f);
	Player.SetPosition(65.0f, GAME_HEIGHT - 185.0f);
	setPlayerSize();
	Player.SetZ(MSS_DEPTH - 1);
	Player.Draw(Data.GetID(Data.GetIMGPlayer(currentPlayerIDPos)));

	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(160.0f, GAME_HEIGHT - 175.0f, MSS_DEPTH - 1, 325.0f, 20.0f, APP_GAME_TEXT);

	glColor3f(1.0f, 1.0f, 1.0f);
	Player.SetPosition(510.0f, GAME_HEIGHT - 185.0f);
	Player.Draw(Data.GetID(Data.GetIMGPlayer(currentPlayerIDPos)));

	//Noms
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(140.0f, GAME_HEIGHT - 250.0f, MSS_DEPTH - 1, 350.0f, 20.0f, CREDITS_ESTER_TEXT);

	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(175.0f, GAME_HEIGHT - 300.0f, MSS_DEPTH - 1, 275.0f, 20.0f, CREDITS_MARC_TEXT);

	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(140.0f, GAME_HEIGHT - 375.0f, MSS_DEPTH - 1, 350.0f, 20.0f, CREDITS_WHERE_TEXT);

	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(185.0f, GAME_HEIGHT - 400.0f, MSS_DEPTH - 1, 250.0f, 20.0f, CREDITS_WHEN_TEXT);

	//Fons
	glColor3f(0.8f, 0.8f, 0.85f);
	drawRectangle(50.0f, 50.0f, MSS_DEPTH - 2, GAME_WIDTH - 100.0f, GAME_HEIGHT - 180.0f);

	glPopMatrix();
}

void cMenu::drawRectangle(float x, float y, float z, float w, float h) {
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + w, y, z);
	glVertex3f(x + w, y + h, z);
	glVertex3f(x, y + h, z);
	glEnd();
}

void cMenu::drawImage(int tex_id, float x, float y, float z, float w, float h) {
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

void cMenu::render_stars() {
	for (int i = 0; i < starsX.size(); ++i) {
		float x = starsX[i];
		float y = starsY[i];
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3f(x, y, MSS_DEPTH - 3);
		glVertex3f(x + 4, y, MSS_DEPTH - 3);
		glVertex3f(x + 4, y + 4, MSS_DEPTH - 3);
		glVertex3f(x, y + 4, MSS_DEPTH - 3);
		glEnd();
	}
}

void cMenu::calculate_stars() {
	for (int i = 0; i < maxStars; ++i) {
		int w = rand() % GAME_WIDTH * 100;
		int h = rand() % GAME_HEIGHT * 100;

		float x = w / 100;
		float y = h / 100;

		starsX[i] = x;
		starsY[i] = y;
	}
}

void cMenu::setPlayerSize() {
	if (Data.GetIMGPlayer(currentPlayerIDPos) == IMG_MEXICAN) {
		Player.SetWidthHeight(4 * TILE_SIZE, 3 * TILE_SIZE);
	}
	else if (Data.GetIMGPlayer(currentPlayerIDPos) == IMG_OKTOBER) {
		Player.SetWidthHeight(3 * TILE_SIZE, 3 * TILE_SIZE);
	}
	else {
		Player.SetWidthHeight(BICHO_WIDTH, BICHO_HEIGHT);
	}
}
