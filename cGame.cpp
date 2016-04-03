#include "cGame.h"

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
	strcpy(path, concat_path(IMAGES_FOLDER, "fondo_cielo4.png").c_str());
	res = Data.LoadImage(IMG_BACKGROUND, path, GL_RGBA);
	if (!res) return false;

	//Layer2 initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "fondo_montana.png").c_str());
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
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_enemy_ninja.png").c_str());
	res = Data.LoadImage(IMG_NINJA, path, GL_RGBA);
	if (!res) return false;

	//Zombie-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_enemy_zombie.png").c_str());
	res = Data.LoadImage(IMG_ZOMBIE, path, GL_RGBA);
	if (!res) return false;

	//Pirate-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_enemy_pirate.png").c_str());
	res = Data.LoadImage(IMG_PIRATE, path, GL_RGBA);
	if (!res) return false;

	//Ninja-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_boss_tac.png").c_str());
	res = Data.LoadImage(IMG_TAC, path, GL_RGBA);
	if (!res) return false;

	//Zombie-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_boss_mummy.png").c_str());
	res = Data.LoadImage(IMG_MUMMY, path, GL_RGBA);
	if (!res) return false;

	//Pirate-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_boss_groudon.png").c_str());
	res = Data.LoadImage(IMG_GROUDON, path, GL_RGBA);
	if (!res) return false;

	//Gradient-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_gradiente.png").c_str());
	res = Data.LoadImage(IMG_GRADIENT, path, GL_RGBA);
	if (!res) return false;

	//Rainbow initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "rainbow2.png").c_str());
	res = Data.LoadImage(IMG_RAINBOW, path, GL_RGBA);
	if (!res) return false;

	//Projectile initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "projectiles.png").c_str());
	res = Data.LoadImage(IMG_PROJ, path, GL_RGBA);
	if (!res) return false;

	//Projectile initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "ninja_stars.png").c_str());
	res = Data.LoadImage(IMG_PROJ_NINJA, path, GL_RGBA);
	if (!res) return false;
	
	//Projectile initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "projectiles_enemy_zombie.png").c_str());
	res = Data.LoadImage(IMG_PROJ_ZOMBIE, path, GL_RGBA);
	if (!res) return false;
	
	//Projectile initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "skulls.png").c_str());
	res = Data.LoadImage(IMG_PROJ_PIRATE, path, GL_RGBA);
	if (!res) return false;

	startGame();

	return res;
}

void cGame::startGame() {
	currentLevel = 1;
	playerLostLife = false;
	gamePaused = false;
	gameEnd = false;
	GameInfoLayer.Init();

	//Reiniciar puntuacion de Player

	loadLevel(currentLevel);
}

bool cGame::loadLevel(int level) {
	Sound.PlayCustomSound(SOUND_NYAN_BASE);
	//Sound.StopCustomSound();
	bool res = true;
	cameraXScene = 0.0f;
	playerLostLife = false;
	bossDead = false;

	MountainLayer.restartLevel();
	SkyLayer.restartLevel();

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
	Enemies = vector<cBicho*>(0);
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
			if (tile == ENEMY_VER) { // Ninja
				cEnemyVertical* enemy = new cEnemyVertical();
				enemy->SetTile(i, j);
				enemy->SetZ(SCENE_DEPTH);
				enemy->SetWidthHeight(BICHO_WIDTH, BICHO_HEIGHT);
				enemy->SetWidthHeightProjectiles(20, 20);
				Scene.SetMapValue(i, j, BICHO_WIDTH, BICHO_HEIGHT, ENEMY_VER - 48);
				Enemies.push_back(enemy);
			}
			else if (tile == ENEMY_HOR) { // Zombi
				cEnemyHorizontal* enemy = new cEnemyHorizontal();
				enemy->SetTile(i, j);
				enemy->SetZ(SCENE_DEPTH);
				enemy->SetWidthHeight(BICHO_WIDTH, BICHO_HEIGHT);
				Scene.SetMapValue(i, j, BICHO_WIDTH, BICHO_HEIGHT, ENEMY_HOR - 48);
				Enemies.push_back(enemy);
			}
			else if (tile == ENEMY_CIR) { // Pirate
				cEnemyCircle* enemy = new cEnemyCircle();
				enemy->SetTile(i, j);
				enemy->SetZ(SCENE_DEPTH);
				enemy->SetWidthHeight(5 * TILE_SIZE, BICHO_HEIGHT);
				enemy->SetWidthHeightProjectiles(20, 20);
				Scene.SetMapValue(i, j, 5*TILE_SIZE, BICHO_HEIGHT, ENEMY_CIR - 48);
				Enemies.push_back(enemy);
			}
			else if (tile == BOSS) {
				Boss.SetTile(i, j);
				Boss.SetZ(SCENE_DEPTH);
				Boss.SetWidthHeight(2*BICHO_WIDTH, 2*BICHO_HEIGHT);
				Scene.SetMapValue(i, j, 2*BICHO_WIDTH, 2*BICHO_HEIGHT, BOSS - 48);
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

	next_game_tick = GetTickCount() + SKIP_TICKS;
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

	// Do not scroll if level is finished
	if (isGameStandBy() || isEndOfMap()) {
		SkyLayer.endOfLevel();
		MountainLayer.endOfLevel();
	}

	if (isGameStandBy()) {
		if (keys[27]) {
			keys[27] = false;
			gameEnd = true;
		}
		else if (keys[13]) {
			if (isPlayerDead()) {
				startGame();
			}
			else if (isPlayerOutsideWindow() || isPlayerLostLife()) {
				loadLevel(currentLevel);
			}
			else if (isEndOfLevel() && currentLevel < TOTAL_LEVELS && isBossDead()) {
				currentLevel++;
				loadLevel(currentLevel);
			}
		}
		else if (keys['p']) {
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

		if (keys['p'] || keys[27]) {
			gamePaused = true;
			keys['p'] = false;
			keys[27] = false;
		}

		float scroll = GAME_SCROLL;
		if (isEndOfMap()) scroll = 0;

		bool playerDead = false;

		//Game Logic
		Player.Logic(Scene.GetMap(), scroll);

		if (isPlayerOutsideWindow()) {
			playerDead = true;
		}

		playerDead = playerDead || checkPlayerPosition();

		Matrix map = Scene.GetMap();
		Player.LogicProjectiles(map);

		for (int i = 0; i < Enemies.size(); ++i) {
			Enemies[i]->Logic(map, scroll);
			Enemies[i]->LogicProjectiles(map,currentLevel, TOTAL_LEVELS);
		}

		Boss.Logic(map, scroll);

		Scene.SetMap(map);

		setBossDead();

		checkCollisionsPlayer();
		//playerDead = playerDead || checkCollisionsEnemies();

		if (playerDead) {
			startSound(SOUND_CAT_DYING);
			GameInfoLayer.SetCurrentLife(GameInfoLayer.GetCurrentLife() - 1);
			playerLostLife = true;
		}
	}

	return res;
}

//Output
void cGame::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);

	if (isGameStandBy()) {
		if (isEndOfLevel()) {
			if (currentLevel == TOTAL_LEVELS) {
				renderMessage(END_OF_GAME);
			}
			else {
				renderMessage(END_OF_LEVEL);
			}
		}
		else if (isPlayerDead()) {
			renderMessage(END_GAME_OVER);
		}
		else if (isGamePaused()) {
			renderMessage(GAME_PAUSED);
		}
		else if (isPlayerOutsideWindow() || isPlayerLostLife()) {
			renderMessage(LIFE_LOST);
		}
	}

	SkyLayer.Draw(Data.GetID(IMG_BACKGROUND));
	MountainLayer.Draw(Data.GetID(IMG_LAYER2), currentLevel);

	UpdateCameraScene();
	Scene.Draw(Data.GetID(IMG_SCENE));

	glColor3f(1.0f, 1.0f, 1.0f);

	Player.Draw(Data.GetID(IMG_PLAYER));
	Player.DrawProjectiles(Data.GetID(IMG_PROJ));

	int tex_id_bicho, tex_id_proj;
	for (int i = 0; i < Enemies.size(); ++i) {
		if (typeid(*Enemies[i]) == typeid(cEnemyVertical)) {
			tex_id_bicho = Data.GetID(IMG_NINJA);
			tex_id_proj = Data.GetID(IMG_PROJ_NINJA);
		}
		else if (typeid(*Enemies[i]) == typeid(cEnemyHorizontal)) {
			tex_id_bicho = Data.GetID(IMG_ZOMBIE);
			tex_id_proj = Data.GetID(IMG_PROJ_ZOMBIE);
		}
		else {
			tex_id_bicho = Data.GetID(IMG_PIRATE);
			tex_id_proj = Data.GetID(IMG_PROJ_PIRATE);
		}
		Enemies[i]->Draw(tex_id_bicho);
		Enemies[i]->DrawProjectiles(tex_id_proj);
	}

	int tex_id_boss, tex_id_boss_proj;
	if (currentLevel == 1) {
		tex_id_boss = Data.GetID(IMG_TAC);
		tex_id_boss_proj = Data.GetID(IMG_PROJ_NINJA);
	}
	else if (currentLevel == 2) {
		tex_id_boss = Data.GetID(IMG_MUMMY);
		tex_id_boss_proj = Data.GetID(IMG_PROJ_ZOMBIE);
	}
	else {
		tex_id_boss = Data.GetID(IMG_GROUDON);
		tex_id_boss_proj = Data.GetID(IMG_PROJ_PIRATE);
	}
	Boss.Draw(tex_id_boss);

	Player.DrawRainbow(Data.GetID(IMG_RAINBOW), cameraXScene);
	RestartCameraScene();

	GameInfoLayer.Draw();

	glutSwapBuffers();
}

bool cGame::isGameStandBy() {
	return isPlayerDead() || isGamePaused() || isPlayerOutsideWindow() || isPlayerLostLife() || isEndOfLevel();
}

bool cGame::isPlayerOutsideWindow() {
	return Player.isOutsideWindow();
}

bool cGame::isPlayerDead() {
	//return Player.isGameOver();
	return GameInfoLayer.GetCurrentLife() == 0;
}

bool cGame::isEndOfLevel() {
	return isEndOfMap() && isBossDead();
}

bool cGame::isEndOfMap() {
	return Scene.endOfMap(cameraXScene + GAME_SCROLL);
}

bool cGame::isGamePaused() {
	return gamePaused;
}

bool cGame::isBossDead() {
	return bossDead;
}

void cGame::SetGameEnd(bool end) {
	gameEnd = end;
}

bool cGame::HasGameEnd() {
	return gameEnd;
}

bool cGame::isPlayerLostLife() {
	return playerLostLife;
}

void cGame::startSound(int sound){
	Sound.PlayCustomSound(sound);
}

void cGame::renderMessage(int message) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_MARCO));

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(GAME_WIDTH / 2 - 200.0f, GAME_HEIGHT / 2 - 100.0f, MSS_DEPTH - 1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(GAME_WIDTH / 2 + 200.0f, GAME_HEIGHT / 2 - 100.0f, MSS_DEPTH - 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(GAME_WIDTH / 2 + 200.0f, GAME_HEIGHT / 2 + 100.0f, MSS_DEPTH - 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(GAME_WIDTH / 2 - 200.0f, GAME_HEIGHT / 2 + 100.0f, MSS_DEPTH - 1);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	if (message == END_OF_LEVEL || message == GAME_PAUSED || message == LIFE_LOST) {
		glColor3f(0.0f, 0.0f, 0.0f);
		char message_main[64];
		char message_second[64];
		if (message == END_OF_LEVEL) {
			strcpy(message_main, END_OF_LEVEL_MESSAGE);
			strcpy(message_second, END_OF_LEVEL_MESSAGE_NEXT);
		}
		else if (message == GAME_PAUSED) {
			strcpy(message_main, GAME_PAUSED_MESSAGE);
			strcpy(message_second, GAME_PAUSED_MESSAGE_NEXT);
		}
		else if (message == LIFE_LOST) {
			strcpy(message_main, PLAYER_LOSES_LIFE_MESSAGE);
			strcpy(message_second, PLAYER_LOSES_LIFE_MESSAGE_NEXT);
		}
		Font.drawText(GAME_WIDTH / 2 - 100.0f, GAME_HEIGHT / 2 - 5.0f, MSS_DEPTH, 200.0f, 50.0f, message_main);
		Font.drawText(GAME_WIDTH / 2 - 150.0f, GAME_HEIGHT / 2 - 45.0f, MSS_DEPTH, 300.0f, 25.0f, message_second);
	}
	else {
		glColor3f(0.0f, 0.0f, 0.0f);

		char message_main[64];
		if (message == END_OF_GAME) {
			strcpy(message_main, END_OF_GAME_MESSAGE);
		}
		if (message == END_GAME_OVER) {
			strcpy(message_main, GAME_OVER_MESSAGE);
		}

		Font.drawText(GAME_WIDTH / 2 - 100.0f, GAME_HEIGHT / 2 + 25.0f, MSS_DEPTH, 200.0f, 40.0f, message_main);

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
}

void cGame::UpdateCameraScene() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(cameraXScene, cameraXScene + GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);

	// If not end of level, map can continue scrolling
	if (!(isGameStandBy() || isEndOfMap())) {
		cameraXScene += GAME_SCROLL;
	}
}

void cGame::RestartCameraScene() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 0 + GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);
}

void cGame::setBossDead() {
	vector<Projectile> projsRight = Player.GetProjectiles(DIR_RIGHT);

	for (int p = 0; p < projsRight.size(); ++p) {
		float px = projsRight[p].x;
		float py = projsRight[p].y;

		if (Boss.GetX() <= px && px <= Boss.GetX() + Boss.GetWidth() &&
			Boss.GetY() <= py && py <= Boss.GetY() + Boss.GetHeight()) {
			bossDead = true;
			Boss.SetWidthHeight(0, 0);

			projsRight.erase(projsRight.begin() + p);
		}
	}

	Player.SetProjectiles(projsRight, DIR_RIGHT);
}

bool cGame::checkPlayerPosition() {
	bool collides = false;
	float xPlayer = Player.GetX();
	float yPlayer = Player.GetY();
	int wPlayer = Player.GetWidth();
	int hPlayer = Player.GetHeight();

	for (int i = 0; i < Enemies.size() && !collides; ++i) {
		float enX = Enemies[i]->GetX();
		float enY = Enemies[i]->GetY();
		float enW = Enemies[i]->GetWidth();
		float enH = Enemies[i]->GetHeight();
		if (isPositionInside(enX, enY, xPlayer, yPlayer, wPlayer, hPlayer) ||
			isPositionInside(enX + enW, enY, xPlayer, yPlayer, wPlayer, hPlayer) ||
			isPositionInside(enX + enW, enY + enH, xPlayer, yPlayer, wPlayer, hPlayer) ||
			isPositionInside(enX, enY + enH, xPlayer, yPlayer, wPlayer, hPlayer)) {
			collides = true;
		}
	}

	return collides;
}

bool cGame::isPositionInside(float x, float y, float xPlayer, float yPlayer, int wPlayer, int hPlayer) {
	if (xPlayer < x && x < xPlayer + wPlayer &&
		yPlayer < y && y < yPlayer + hPlayer) {
		return true;
	}

	return false;
}

void cGame::checkCollisionsPlayer() {
	vector<Projectile> projsRight = Player.GetProjectiles(DIR_RIGHT);

	for (int p = 0; p < projsRight.size(); ++p) {
		int tx = projsRight[p].x / TILE_SIZE;
		int ty = projsRight[p].y / TILE_SIZE;
		int tx2 = tx + 1;

		if (Scene.isEnemy(tx, ty) || Scene.isEnemy(tx2, ty)) {
			bool found = false;
			for (int v = 0; v < Enemies.size() && !found; ++v) {
				int v_tx = Enemies[v]->GetX() / TILE_SIZE;
				int v_ty = Enemies[v]->GetY() / TILE_SIZE;
				int v_tx2 = (Enemies[v]->GetX() + Enemies[v]->GetWidth()) / TILE_SIZE;
				int v_ty2 = (Enemies[v]->GetY() + Enemies[v]->GetHeight()) / TILE_SIZE;

				if (((tx >= v_tx && tx <= v_tx2) || (tx2 >= v_tx && tx2 <= v_tx2)) && ty >= v_ty && ty <= v_ty2) {
					found = true;
					Enemies.erase(Enemies.begin() + v);
					projsRight.erase(projsRight.begin() + p);
					Scene.SetMapValue(v_tx, v_ty, BICHO_WIDTH, BICHO_HEIGHT, 0);

					GameInfoLayer.SetCurrentScore(GameInfoLayer.GetCurrentScore() + 1);
				}
			}
		}
	}

	Player.SetProjectiles(projsRight, DIR_RIGHT);
}

bool cGame::checkCollisionsEnemies() {
	bool collides = false;
	for (int i = 0; i < Enemies.size() && !collides; ++i) {
		collides = checkProjectilesEnemy(Enemies[i]->GetProjectiles(DIR_RIGHT));
		collides = collides || checkProjectilesEnemy(Enemies[i]->GetProjectiles(DIR_LEFT));
	}

	return collides;
}

bool cGame::checkProjectilesEnemy(vector<Projectile>& projs) {
	for (int p = 0; p < projs.size(); ++p) {
		float projX = projs[p].x;
		float projY = projs[p].y;

		if (projX >= Player.GetX() && projX + PROJ_WIDTH <= Player.GetX() + Player.GetWidth() &&
			projY >= Player.GetY() && projY + PROJ_HEIGHT <= Player.GetY() + Player.GetHeight()) {
			// Proyectile hit Player
			return true;
		}
	}
	return false;
}
