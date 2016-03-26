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

	char player_path[64];
	strcpy(player_path, IMAGES_FOLDER);
	strcat(player_path, "/");
	strcat(player_path, "nyancat_alas.png");
	res = Data.LoadImage(IMG_PLAYER, player_path, GL_RGBA);
	if (!res) return false;

	char keyboard_arrow_path[64];
	strcpy(keyboard_arrow_path, IMAGES_FOLDER);
	strcat(keyboard_arrow_path, "/");
	strcat(keyboard_arrow_path, "keyboard_arrows.png");
	res = Data.LoadImage(IMG_KEYBOARD, keyboard_arrow_path, GL_RGBA);
	if (!res) return false;

	Font.setFont(Data.GetID(IMG_FONT), 256, 256, 19, 29);
	//Sound.PlayCustomSound(SOUND_NYAN_BASE);
	calculate_stars();

	return res;
}

bool cMenu::Loop()
{
	bool res = true;

	res = Process();
	if (res) Render();

	next_game_tick += SKIP_TICKS;
	sleep_time = next_game_tick - GetTickCount();
	if (sleep_time >= 0) {
		Sleep(sleep_time);
	}
	else {
		// Shit, we are running behind!
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
		if (keys[27]) {
			switch (internalState) {
			case MENU:
				res = false;
				break;
			case HOW_TO:
				showMenu();
				internalState = MENU;
				break;
			case CREDITS:
				showMenu();
				internalState = MENU;
				break;
			}
		}

		if (keys[GLUT_KEY_UP]) {
			moveAction(-1);
		}
		else if (keys[GLUT_KEY_DOWN]) {
			moveAction(1);
		}

		if (keys[13]) {
			executeAction();
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

	for (int i = 0; i < starsX.size(); ++i) {
		float x = starsX[i];
		float y = starsY[i];
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(x, y, MSS_DEPTH-3);
			glVertex3f(x+3.5f, y, MSS_DEPTH-3);
			glVertex3f(x+3.5f, y+3.5f, MSS_DEPTH-3);
			glVertex3f(x, y+3.5f, MSS_DEPTH-3);
		glEnd();
	}

	switch (internalState) {
	case MENU:
		showMenu();
		break;
	case HOW_TO:
		showInstrucctions();
		break;
	case CREDITS:
		showCredits();
		break;
	}

	glutSwapBuffers();
}

//State in use
int cMenu::GetState() {
	return currentState;
}

void cMenu::executeAction() {
	if (actionSelected == gameAction) {
		currentState = GAME;
	}
	else if (actionSelected == howtoAction) {
		//Sound.StopCustomSound(); //TODO only to test
		internalState = HOW_TO;
	}
	else if (actionSelected == creditsAction) {
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
		}
	}
	else if (actionSelected == howtoAction) {
		if (moveTo == 1) {
			actionSelected = creditsAction;
		}
		else if (moveTo == -1) {
			actionSelected = gameAction;
		}
	}
	else if (actionSelected == creditsAction) {
		if (moveTo == 1) {
			actionSelected = stopAction;
		}
		else if (moveTo == -1) {
			actionSelected = howtoAction;
		}
	}
	else if (actionSelected == stopAction) {
		if (moveTo == -1) {
			actionSelected = creditsAction;
		}
	}
}

void cMenu::showMenu() {
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 105.0f, GAME_HEIGHT / 2.0f + 130.0f, MSS_DEPTH, 200.0f, 50.0f, PLAY_TEXT);

	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 100.0f, GAME_HEIGHT / 2.0f + 30.0f, MSS_DEPTH, 200.0f, 50.0f, HOW_TO_TEXT);

	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 100.0f, GAME_HEIGHT / 2.0f - 70.0f, MSS_DEPTH, 200.0f, 50.0f, CREDITS_TEXT);

	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 105.0f, GAME_HEIGHT / 2.0f - 170.0f, MSS_DEPTH, 200.0f, 50.0f, EXIT_TEXT);
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

	if (actionSelected == creditsAction)
		glColor3f(1.0f, 1.0f, 0.0f);
	else
		glColor3f(0.5f, 0.5f, 0.5f);
	drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f - 85.0f, MSS_DEPTH - 1, 300.0f, 75.0f);

	if (actionSelected == stopAction)
		glColor3f(0.0f, 0.0f, 1.0f);
	else
		glColor3f(0.5f, 0.5f, 0.5f);
	drawRectangle(GAME_WIDTH / 2.0f - 150.0f, GAME_HEIGHT / 2.0f - 185.0f, MSS_DEPTH - 1, 300.0f, 75.0f);
}

void cMenu::showInstrucctions() {
	glPushMatrix();

	//Instruccions titol
	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 160.0f, GAME_HEIGHT / 2.0f + 160.0f, MSS_DEPTH-1, 300.0f, 40.0f, HOW_TO_TEXT);

	//Explicacio 1
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(65.0f, GAME_HEIGHT - 165.0f, MSS_DEPTH-1, 350.0f, 20.0f, HOW_TO_PLAYER_TEXT_1);

	//Nyan Image
	glColor3f(1.0f, 1.0f, 1.0f);
	Player.SetPosition(GAME_WIDTH / 2.0f - 40.0f, GAME_HEIGHT - 235.0f);
	Player.SetWidthHeight(3 * TILE_SIZE, 2 * TILE_SIZE);
	Player.SetZ(MSS_DEPTH-1);
	Player.Draw(Data.GetID(IMG_PLAYER));

	//Explicacio 2
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(65.0f, GAME_HEIGHT - 300.0f, MSS_DEPTH-1, 500.0f, 20.0f, HOW_TO_PLAYER_TEXT_2);

	//Keyboard Image
	glColor3f(1.0f, 1.0f, 1.0f);
	drawImage(Data.GetID(IMG_KEYBOARD), GAME_WIDTH / 2.0f - 105.0f, 60.0f, MSS_DEPTH-1, 200.0f, 120.0f);

	//Fons
	glColor3f(0.8f, 0.8f, 0.85f);
	drawRectangle(50.0f, 50.0f, MSS_DEPTH - 2, GAME_WIDTH - 100.0f, GAME_HEIGHT - 180.0f);

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
	Player.SetWidthHeight(3 * TILE_SIZE, 2 * TILE_SIZE);
	Player.SetZ(MSS_DEPTH - 1);
	Player.Draw(Data.GetID(IMG_PLAYER));

	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(160.0f, GAME_HEIGHT - 175.0f, MSS_DEPTH - 1, 325.0f, 20.0f, APP_GAME_TEXT);

	glColor3f(1.0f, 1.0f, 1.0f);
	Player.SetPosition(510.0f, GAME_HEIGHT - 185.0f);
	Player.Draw(Data.GetID(IMG_PLAYER));

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
