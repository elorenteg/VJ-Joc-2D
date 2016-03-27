#include "cGame.h"

bool firstRender;

string concat_path(string folder, string file) {
	string path = folder + "/" + file;
	return path;
}

cGame::cGame(void) {
}

cGame::~cGame(void) {
}

bool cGame::Init() {
	bool res = true;

	//Graphics initialization
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	char path[64];

	//Background initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "fondo_cielo.png").c_str());
	res = Data.LoadImage(IMG_BACKGROUND, path, GL_RGBA);
	if (!res) return false;

	//Layer2 initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "fondo_capa2.png").c_str());
	res = Data.LoadImage(IMG_LAYER2, path, GL_RGBA);
	if (!res) return false;

	//Scene map initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "escena.png").c_str());
	res = Data.LoadImage(IMG_SCENE, path, GL_RGBA);
	if (!res) return false;

	//Player initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_alas.png").c_str());
	res = Data.LoadImage(IMG_PLAYER, path, GL_RGBA);
	if (!res) return false;

	//Font initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "font.png").c_str());
	res = Data.LoadImage(IMG_FONT, path, GL_RGBA);
	if (!res) return false;
	Font.setFont(Data.GetID(IMG_FONT), 256, 256, 19, 29);

	//Marco initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "marco_rosa.png").c_str());
	res = Data.LoadImage(IMG_MARCO, path, GL_RGBA);
	if (!res) return false;

	//Ninja-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_ninja.png").c_str());
	res = Data.LoadImage(IMG_NINJA, path, GL_RGBA);
	if (!res) return false;

	//Gradient-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_gradiente.png").c_str());
	res = Data.LoadImage(IMG_GRADIENT, path, GL_RGBA);
	if (!res) return false;

	//Rainbow initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "rainbow.png").c_str());
	res = Data.LoadImage(IMG_RAINBOW, path, GL_RGBA);
	if (!res) return false;

	//Projectile initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "projectiles.png").c_str());
	res = Data.LoadImage(IMG_SHOOT, path, GL_RGBA);
	if (!res) return false;

	startGame();

	return res;
}

void cGame::startGame() {
	currentLevel = 1;
	GameInfoLayer.Init();

	//Reiniciar puntuacion de Player

	loadLevel(currentLevel);
}

bool cGame::loadLevel(int level) {
	bool res = true;
	firstRender = true;
	cameraXScene = 0.0f;

	GameInfoLayer.SetCurrentLevel(level);

	// Load level
	res = Scene.LoadLevel(level);
	if (!res) return false;

	// Player initialization
	Player.SetTile(2, SCENE_HEIGHT / 2);
	Player.SetZ(SCENE_DEPTH);
	Player.SetWidthHeight(BICHO_WIDTH, BICHO_HEIGHT);
	Player.SetMapValue(Scene.GetMap(), 2, SCENE_HEIGHT / 2, PLAYER - 48);
	Player.ResetLife();

	// Enemies initialization
	EnemiesV = vector<cEnemyVertical>(0);
	EnemiesH = vector<cEnemyHorizontal>(0);
	EnemiesC = vector<cEnemyCircle>(0);
	res = initEnemies(level);
	if (!res) return false;

	return res;
}

bool cGame::initEnemies(int level) {
	bool res;
	FILE *fd;
	int i, j, px, py;
	char tile;

	res = true;

	char scene_path[128];
	char leveltext[8];
	strcpy(scene_path, LEVELS_FOLDER);
	strcat(scene_path, "/");
	strcat(scene_path, FILENAME);
	sprintf(leveltext, "%d", level);
	strcat(scene_path, leveltext);
	strcat(scene_path, FILENAME_EXT);

	fd = fopen(scene_path, "r");
	if (fd == NULL) return false;

	for (j = SCENE_HEIGHT - 1; j >= 0; j--) {
		px = 0;
		py = j*TILE_SIZE;

		for (i = 0; i < SCENE_WIDTH; i++) {
			fscanf(fd, "%c", &tile);
			if (tile == ENEMY_VER) {
				cEnemyVertical enemy;
				enemy.SetTile(i, j);
				enemy.SetZ(SCENE_DEPTH);
				enemy.SetWidthHeight(BICHO_WIDTH, BICHO_HEIGHT);
				enemy.SetMapValue(Scene.GetMap(), i, j, ENEMY_VER - 48);
				EnemiesV.push_back(enemy);
			}
			else if (tile == ENEMY_HOR) {
				cEnemyHorizontal enemy;
				enemy.SetTile(i, j);
				enemy.SetZ(SCENE_DEPTH);
				enemy.SetWidthHeight(BICHO_WIDTH, BICHO_HEIGHT);
				enemy.SetMapValue(Scene.GetMap(), i, j, ENEMY_HOR - 48);
				EnemiesH.push_back(enemy);
			}
			else if (tile == ENEMY_CIR) {
				cEnemyCircle enemy;
				enemy.SetTile(i, j);
				enemy.SetZ(SCENE_DEPTH);
				enemy.SetWidthHeight(BICHO_WIDTH, BICHO_HEIGHT);
				enemy.SetMapValue(Scene.GetMap(), i, j, ENEMY_CIR - 48);
				EnemiesC.push_back(enemy);
			}
		}
		fscanf(fd, "%c", &tile); //pass enter
	}

	fclose(fd);

	return res;
}

bool cGame::Loop() {
	bool res = true;

	res = Process();
	if (res) Render();

	if (firstRender) {
		next_game_tick = GetTickCount();
		firstRender = false;
	}

	next_game_tick += SKIP_TICKS;
	sleep_time = next_game_tick - GetTickCount();
	if (sleep_time >= 0) {
		Sleep(sleep_time);
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

	if (isGameStandBy()) {
		if (keys[13]) {
			if (isPlayerDead()) {
				startGame();
			}
			else if (isEndOfLevel() && currentLevel < TOTAL_LEVELS) {
				currentLevel++;
				loadLevel(currentLevel);
			}
		}
		if (keys['p']) {
			gamePaused = false;
			keys['p'] = false;
		}
	}
	else {
		if (keys[GLUT_KEY_UP]) {
			Player.MoveUp(Scene.GetMap());
		}
		else if (keys[GLUT_KEY_DOWN]) {
			Player.MoveDown(Scene.GetMap());
		}

		if (keys[GLUT_KEY_LEFT]) {
			Player.MoveLeft(Scene.GetMap());
		}
		else if (keys[GLUT_KEY_RIGHT]) {
			Player.MoveRight(Scene.GetMap());
		}

		if (keys[' ']) {
			Player.Shoot(Scene.GetMap());
			keys[' '] = false;
		}

		if (keys['p']) {
			gamePaused = true;
			keys['p'] = false;
		}

		//Game Logic
		Player.Logic(Scene.GetMap(), GAME_SCROLL);

		Matrix map = Scene.GetMap();
		Player.LogicProjectiles(map, EnemiesV, EnemiesH, EnemiesC);

		for (int i = 0; i < EnemiesH.size(); ++i) {
			EnemiesH[i].Logic(map, GAME_SCROLL);
			EnemiesH[i].LogicProjectiles(map);
		}
		for (int i = 0; i < EnemiesV.size(); ++i) {
			EnemiesV[i].Logic(map, GAME_SCROLL);
			EnemiesV[i].LogicProjectiles(map);
		}
		for (int i = 0; i < EnemiesC.size(); ++i) {
			EnemiesC[i].Logic(map, GAME_SCROLL);
			EnemiesC[i].LogicProjectiles(map);
		}
		Scene.SetMap(map);

		GameInfoLayer.SetCurrentScore(Player.GetScore());
	}

	return res;
}

bool cGame::isGameStandBy() {
	return isPlayerDead() || isEndOfLevel() || isGamePaused();
}

bool cGame::isPlayerDead() {
	return Player.isGameOver();
}

bool cGame::isEndOfLevel() {
	return Scene.endOfMap(cameraXScene + GAME_SCROLL);
}

bool cGame::isGamePaused() {
	return gamePaused;
}

//Output
void cGame::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	// Do not scroll if level is finished
	if (isGameStandBy()) {
		SkyLayer.endOfGame();
		MountainLayer.endOfGame();

		if (isEndOfLevel()) {
			if (currentLevel == TOTAL_LEVELS) {
				RenderMessage(END_OF_GAME);
			}
			else {
				RenderMessage(END_OF_LEVEL);
			}
		}
		else if (isPlayerDead()) {
			RenderMessage(END_GAME_OVER);
		}
		else if (isGamePaused()) {
			RenderMessage(GAME_PAUSED);
		}
	}

	SkyLayer.Draw(Data.GetID(IMG_BACKGROUND));
	MountainLayer.Draw(Data.GetID(IMG_LAYER2));

	UpdateCameraScene();
	Scene.Draw(Data.GetID(IMG_SCENE));

	glColor3f(1.0f, 1.0f, 1.0f);

	Player.Draw(Data.GetID(IMG_PLAYER));
	Player.DrawProjectiles(Data.GetID(IMG_SHOOT));

	for (int i = 0; i < EnemiesH.size(); ++i) {
		EnemiesH[i].Draw(Data.GetID(IMG_NINJA));
		EnemiesH[i].DrawProjectiles(Data.GetID(IMG_SHOOT));
	}
	for (int i = 0; i < EnemiesV.size(); ++i) {
		EnemiesV[i].Draw(Data.GetID(IMG_NINJA));
		EnemiesV[i].DrawProjectiles(Data.GetID(IMG_SHOOT));
	}
	for (int i = 0; i < EnemiesC.size(); ++i) {
		EnemiesC[i].Draw(Data.GetID(IMG_NINJA));
		EnemiesC[i].DrawProjectiles(Data.GetID(IMG_SHOOT));
	}

	Player.DrawRainbow(Data.GetID(IMG_RAINBOW), cameraXScene);
	RestartCameraScene();

	GameInfoLayer.Draw();

	glutSwapBuffers();
}

void cGame::RenderMessage(int message) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_MARCO));

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(GAME_WIDTH / 2 - 200.0f, GAME_HEIGHT / 2 - 100.0f, MSS_DEPTH - 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(GAME_WIDTH / 2 + 200.0f, GAME_HEIGHT / 2 - 100.0f, MSS_DEPTH - 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(GAME_WIDTH / 2 + 200.0f, GAME_HEIGHT / 2 + 100.0f, MSS_DEPTH - 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(GAME_WIDTH / 2 - 200.0f, GAME_HEIGHT / 2 + 100.0f, MSS_DEPTH - 1);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	if (message == END_GAME_OVER) {
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(GAME_WIDTH / 2 - 100.0f, GAME_HEIGHT / 2 - 20.0f, MSS_DEPTH, 200.0f, 50.0f, GAME_OVER_MESSAGE);
	}
	else if (message == END_OF_LEVEL) {
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(GAME_WIDTH / 2 - 100.0f, GAME_HEIGHT / 2 - 5.0f, MSS_DEPTH, 200.0f, 50.0f, END_OF_LEVEL_MESSAGE);
		Font.drawText(GAME_WIDTH / 2 - 150.0f, GAME_HEIGHT / 2 - 45.0f, MSS_DEPTH, 300.0f, 25.0f, END_OF_LEVEL_MESSAGE_NEXT);
	}
	else if (message == END_OF_GAME) {
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(GAME_WIDTH / 2 - 100.0f, GAME_HEIGHT / 2 + 25.0f, MSS_DEPTH, 200.0f, 40.0f, END_OF_GAME_MESSAGE);

		char msgbuf[128];
		char intbuf[8];
		sprintf(intbuf, "%d", GameInfoLayer.GetCurrentScore());
		strcpy(msgbuf, END_SCORE_MESSAGE);
		strcat(msgbuf, ":   ");
		strcat(msgbuf, intbuf);
		Font.drawText(GAME_WIDTH / 2 - 150.0f, GAME_HEIGHT / 2 - 20.0f, MSS_DEPTH, 300.0f, 20.0f, msgbuf);

		sprintf(intbuf, "%d", GameInfoLayer.GetCurrentLife());
		strcpy(msgbuf, END_LIFE_REM_MESSAGE);
		strcat(msgbuf, ":   ");
		strcat(msgbuf, intbuf);
		Font.drawText(GAME_WIDTH / 2 - 150.0f, GAME_HEIGHT / 2 - 45.0f, MSS_DEPTH, 300.0f, 20.0f, msgbuf);

		sprintf(intbuf, "%d", GameInfoLayer.GetCurrentScore() * GameInfoLayer.GetCurrentLife());
		strcpy(msgbuf, END_TOTAL_SCORE_MESSAGE);
		strcat(msgbuf, ":   ");
		strcat(msgbuf, intbuf);
		Font.drawText(GAME_WIDTH / 2 - 150.0f, GAME_HEIGHT / 2 - 70.0f, MSS_DEPTH, 300.0f, 20.0f, msgbuf);

		GameInfoLayer.SaveHighScore(GameInfoLayer.GetCurrentScore() * GameInfoLayer.GetCurrentLife());
	}
	else if (message == GAME_PAUSED) {
		glColor3f(0.0f, 0.0f, 0.0f);
		Font.drawText(GAME_WIDTH / 2 - 100.0f, GAME_HEIGHT / 2 - 5.0f, MSS_DEPTH, 200.0f, 50.0f, GAME_PAUSED_MESSAGE);
		Font.drawText(GAME_WIDTH / 2 - 150.0f, GAME_HEIGHT / 2 - 45.0f, MSS_DEPTH, 300.0f, 25.0f, GAME_PAUSED_MESSAGE_NEXT);
	}
}

void cGame::UpdateCameraScene() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(cameraXScene, cameraXScene + GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);

	// If not end of level, map can continue scrolling
	if (!isGameStandBy()) {
		cameraXScene += GAME_SCROLL;
	}
}

void cGame::RestartCameraScene() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 0 + GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);
}
