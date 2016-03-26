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

	Player.SetTile(25, 20);

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
			glVertex3f(x, y, MSS_DEPTH-2);
			glVertex3f(x+3.5f, y, MSS_DEPTH-2);
			glVertex3f(x+3.5f, y+3.5f, MSS_DEPTH-2);
			glVertex3f(x, y+3.5f, MSS_DEPTH-2);
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

	Player.Draw(Data.GetID(IMG_PLAYER));

	//Instruccions titol
	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 160.0f, GAME_HEIGHT / 2.0f + 160.0f, MSS_DEPTH, 300.0f, 40.0f, HOW_TO_TEXT);

	//Explicacio
	glColor3f(0.0f, 0.0f, 0.0f);
	Font.drawText(65.0f, GAME_HEIGHT - 165.0f, MSS_DEPTH, 350.0f, 20.0f, HOW_TO_PLAYER_TEXT_1);

	Font.drawText(65.0f, GAME_HEIGHT - 295.0f, MSS_DEPTH, 500.0f, 20.0f, HOW_TO_PLAYER_TEXT_2);

	//Fons
	glColor3f(0.8f, 0.8f, 0.85f);
	drawRectangle(50.0f, 50.0f, MSS_DEPTH - 1, GAME_WIDTH - 100.0f, GAME_HEIGHT - 180.0f);

	glPopMatrix();
}

void cMenu::showCredits() {
	glPushMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
	Font.drawText(GAME_WIDTH / 2.0f - 105.0f, GAME_HEIGHT / 2.0f + 150.0f, MSS_DEPTH, 200.0f, 40.0f, CREDITS_TEXT);
	
	glPopMatrix();
}

// Draw the rectangle
void cMenu::drawRectangle(float x, float y, float z, float width, float height) {
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x, y + height, z);
	glEnd();
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
