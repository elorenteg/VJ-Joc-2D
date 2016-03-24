#include "cGame.h"

cGame::cGame(void) {
}

cGame::~cGame(void) {
}

bool cGame::Init() {
	bool res = true;
	cameraXScene = 0;
	isGameOver = false;
	int level = 10;

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
	res = Data.LoadImage(IMG_SCENE, scene_path, GL_RGBA);
	if (!res) return false;
	res = Scene.LoadLevel(level);
	if (!res) return false;

	//Player initialization
	char player_path[64];
	strcpy(player_path, IMAGES_FOLDER);
	strcat(player_path, "/");
	strcat(player_path, "nyancat_alas.png");
	res = Data.LoadImage(IMG_PLAYER, player_path, GL_RGBA);
	if (!res) return false;
	Player.SetTile(2, SCENE_HEIGHT/2);
	Player.SetWidthHeight(60, 40);

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

	char ninja_path[64];
	strcpy(ninja_path, IMAGES_FOLDER);
	strcat(ninja_path, "/");
	strcat(ninja_path, "nyancat_ninja.png");
	res = Data.LoadImage(IMG_NINJA, ninja_path, GL_RGBA);
	if (!res) return false;

	char gradient_path[64];
	strcpy(gradient_path, IMAGES_FOLDER);
	strcat(gradient_path, "/");
	strcat(gradient_path, "nyancat_gradiente.png");
	res = Data.LoadImage(IMG_GRADIENT, gradient_path, GL_RGBA);
	if (!res) return false;

	res = InitEnemies(level);
	if (!res) return 
	
	GameInfoLayer.Init();

	return res;
}

bool cGame::InitEnemies(int level) {
	bool res;
	FILE *fd;
	int i, j, px, py;
	char tile;

	res = true;

	string scene_path;
	if (level == 1) scene_path = LEVELS_FOLDER "/" FILENAME "1" FILENAME_EXT;
	else if (level == 2) scene_path = LEVELS_FOLDER "/" FILENAME "2" FILENAME_EXT;
	else if (level == 3) scene_path = LEVELS_FOLDER "/" FILENAME "3" FILENAME_EXT;
	else if (level == 10) scene_path = LEVELS_FOLDER "/" FILENAME "10" FILENAME_EXT;

	fd = fopen(scene_path.c_str(), "r");
	if (fd == NULL) return false;

	for (j = SCENE_HEIGHT - 1; j >= 0; j--) {
		px = 0;
		py = j*TILE_SIZE;

		for (i = 0; i<SCENE_WIDTH; i++) {
			fscanf(fd, "%c", &tile);
			if (tile == ENEMY_VER) {
				cEnemyVertical enemy;
				enemy.SetTile(i, j);
				enemy.SetWidthHeight(60, 40);

				EnemiesV.push_back(enemy);
				//addEnemy(enemy);

				Matrix map = Scene.GetMap();

				for (int ii = 0; ii < 60 / TILE_SIZE; ++ii) {
					for (int jj = 0; jj < 40 / TILE_SIZE; ++jj) {
						map[j + jj][i + ii] = ENEMY_VER - 48;
					}
				}

				Scene.SetMap(map);
			}

			else if (tile == ENEMY_HOR) {
				cEnemyHorizontal enemy;
				enemy.SetTile(i, j);
				enemy.SetWidthHeight(60, 40);

				EnemiesH.push_back(enemy);

				//addEnemy(enemy);

				Matrix map = Scene.GetMap();

				for (int ii = 0; ii < 60 / TILE_SIZE; ++ii) {
					for (int jj = 0; jj < 40 / TILE_SIZE; ++jj) {
						map[j + jj][i + ii] = ENEMY_HOR - 48;
					}
				}

				Scene.SetMap(map);
			}

			else if (tile == ENEMY_CIR) {
				cEnemyCircle enemy;
				enemy.SetTile(i, j);
				enemy.SetWidthHeight(60, 40);

				EnemiesC.push_back(enemy);

				//addEnemy(enemy);

				Matrix map = Scene.GetMap();

				for (int ii = 0; ii < 60 / TILE_SIZE; ++ii) {
					for (int jj = 0; jj < 40 / TILE_SIZE; ++jj) {
						map[j + jj][i + ii] = ENEMY_CIR - 48;
					}
				}

				Scene.SetMap(map);
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
		if (keys[GLUT_KEY_UP]) {
			Player.MoveUp(Scene.GetMap());
			//keys[GLUT_KEY_UP] = false;
		}
		else if (keys[GLUT_KEY_DOWN]) {
			Player.MoveDown(Scene.GetMap());
			//keys[GLUT_KEY_DOWN] = false;
		}

		if (keys[GLUT_KEY_LEFT]) {
			Player.MoveLeft(Scene.GetMap());
			//keys[GLUT_KEY_LEFT] = false;
		}
		else if (keys[GLUT_KEY_RIGHT]) {
			Player.MoveRight(Scene.GetMap());
			//keys[GLUT_KEY_RIGHT] = false;
		}

		//Game Logic
		Player.Logic(Scene.GetMap(), GAME_SCROLL);

		Matrix map = Scene.GetMap();
		for (int i = 0; i < EnemiesH.size(); ++i) {
			EnemiesH[i].Logic(map);
		}
		for (int i = 0; i < EnemiesV.size(); ++i) {
			EnemiesV[i].Logic(map);
		}
		for (int i = 0; i < EnemiesC.size(); ++i) {
			EnemiesC[i].Logic(map);
		}

		Scene.SetMap(map);

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
	Scene.Draw(Data.GetID(IMG_SCENE));

	Player.Draw(Data.GetID(IMG_PLAYER));

	for (int i = 0; i < EnemiesH.size(); ++i) {
		EnemiesH[i].Draw(Data.GetID(IMG_NINJA));
	}
	for (int i = 0; i < EnemiesV.size(); ++i) {
		EnemiesV[i].Draw(Data.GetID(IMG_NINJA));
	}
	for (int i = 0; i < EnemiesC.size(); ++i) {
		EnemiesC[i].Draw(Data.GetID(IMG_NINJA));
	}
	RestartCameraScene();

	if (isEndOfGame()) RenderMessage();

	GameInfoLayer.Draw();

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
