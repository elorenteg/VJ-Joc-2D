#include "cGame.h"

cGame::cGame(void) {
}

cGame::~cGame(void) {
}

bool cGame::Init() {
	bool res = true;
	cameraXScene = 0;
	isGameOver = false;

	//Graphics initialization
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Background initialization
	char backgr_path[64];
	strcpy(backgr_path, IMAGES_FOLDER);
	strcat(backgr_path, "/");
	strcat(backgr_path, "fondo_cielo.png");
	res = Data.LoadImage(IMG_BACKGROUND, backgr_path, GL_RGBA);
	if (!res) return false;

	//Layer2 initialization
	char layer2_path[64];
	strcpy(layer2_path, IMAGES_FOLDER);
	strcat(layer2_path, "/");
	strcat(layer2_path, "fondo_capa2.png");
	res = Data.LoadImage(IMG_LAYER2, layer2_path, GL_RGBA);
	if (!res) return false;

	//Scene map initialization
	char scene_path[64];
	strcpy(scene_path, IMAGES_FOLDER);
	strcat(scene_path, "/");
	strcat(scene_path, "escena.png");
	res = Data.LoadImage(IMG_BLOCKS, scene_path, GL_RGBA);
	if (!res) return false;
	res = Scene.LoadLevel(10);
	if (!res) return false;

	//Player initialization
	char player_path[64];
	strcpy(player_path, IMAGES_FOLDER);
	strcat(player_path, "/");
	strcat(player_path, "nyancat_alas.png");
	res = Data.LoadImage(IMG_PLAYER, player_path, GL_RGBA);
	if (!res) return false;
	Player.SetTile(2, SCENE_HEIGHT/2);
	Player.SetWidthHeight(64, 40);
	//Player.SetState(STATE_LOOKRIGHT);

	char font_path[64];
	strcpy(font_path, IMAGES_FOLDER);
	strcat(font_path, "/");
	strcat(font_path, "font.png");
	res = Data.LoadImage(IMG_FONT, font_path, GL_RGBA);
	if (!res) return false;
	Font.setFont(Data.GetID(IMG_FONT), 256, 256, 19, 29);

	char marco_path[64];
	strcpy(marco_path, IMAGES_FOLDER);
	strcat(marco_path, "/");
	strcat(marco_path, "marco_rosa.png");
	res = Data.LoadImage(IMG_MARCO, marco_path, GL_RGBA);
	if (!res) return false;

	return res;
}

bool cGame::Loop() {
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

	return res;
}

void cGame::Finalize() {
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press) {
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y) {
}

//Process
bool cGame::Process() {
	bool res = true;

	//Process Input
	if (keys[27]) res = false;

	if (!isEndOfGame()) {
		if (keys[GLUT_KEY_UP])
			Player.MoveUp(Scene.GetMap());
		else if (keys[GLUT_KEY_DOWN])
			Player.MoveDown(Scene.GetMap());

		if (keys[GLUT_KEY_LEFT])
			Player.MoveLeft(Scene.GetMap());
		else if (keys[GLUT_KEY_RIGHT])
			Player.MoveRight(Scene.GetMap());

		//Game Logic
		Player.Logic(Scene.GetMap(), GAME_SCROLL);

		isGameOver = Player.isGameOver();
	}

	return res;
}

bool cGame::isEndOfGame() {
	return Player.isGameOver() || Scene.endOfMap(cameraXScene + GAME_SCROLL);
}

//Output
void cGame::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	// If end of game, map do not scroll
	if (isEndOfGame()) {
		SkyLayer.endOfGame();
		MountainLayer.endOfGame();
	}

	SkyLayer.Draw(Data.GetID(IMG_BACKGROUND));
	MountainLayer.Draw(Data.GetID(IMG_LAYER2));

	UpdateCameraScene();
	Scene.Draw(Data.GetID(IMG_BLOCKS));

	Player.Draw(Data.GetID(IMG_PLAYER));
	RestartCameraScene();

	if (isEndOfGame()) RenderMessage();

	glutSwapBuffers();
}

void cGame::RenderMessage() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_MARCO));

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(GAME_WIDTH/2 - 200.0f, GAME_HEIGHT/2 - 100.0f, MSS_DEPTH-1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(GAME_WIDTH/2 + 200.0f, GAME_HEIGHT/2 - 100.0f, MSS_DEPTH-1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(GAME_WIDTH/2 + 200.0f, GAME_HEIGHT/2 + 100.0f, MSS_DEPTH-1);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(GAME_WIDTH/2 - 200.0f, GAME_HEIGHT/2 + 100.0f, MSS_DEPTH-1);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	if (isGameOver) {
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(GAME_WIDTH / 2 - 100.0f, GAME_HEIGHT / 2 - 20.0f, MSS_DEPTH, 200.0f, 50.0f, "GAME OVER");
	}
	else {
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(GAME_WIDTH / 2 - 100.0f, GAME_HEIGHT / 2 - 20.0f, MSS_DEPTH, 200.0f, 50.0f, "THE END");
	}
}

void cGame::UpdateCameraScene() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(cameraXScene, cameraXScene + GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);

	// If not end of game, map can continue scrolling
	if (!isEndOfGame()) cameraXScene += GAME_SCROLL;
}

void cGame::RestartCameraScene() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 0 + GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);
}
