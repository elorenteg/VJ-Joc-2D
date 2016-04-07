#include "cGame.h"

bool initializedCounter;

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
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_player_wings.png").c_str());
	res = Data.LoadImage(IMG_WINGS, path, GL_RGBA);
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

	//Tac-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_boss_tac.png").c_str());
	res = Data.LoadImage(IMG_TAC, path, GL_RGBA);
	if (!res) return false;

	//Mummy-nyancat initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "nyancat_boss_mummy.png").c_str());
	res = Data.LoadImage(IMG_MUMMY, path, GL_RGBA);
	if (!res) return false;

	//Groudon-nyancat initialization
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

	//Projectile initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "projectiles_boss.png").c_str());
	res = Data.LoadImage(IMG_PROJ_BOSS, path, GL_RGBA);
	if (!res) return false;

	//Bubbles initialization
	strcpy(path, concat_path(IMAGES_FOLDER, "burbujas_2.png").c_str());
	res = Data.LoadImage(IMG_BURBUJA, path, GL_RGBA);
	if (!res) return false;

	currentPlayerID = DataManager.readPlayerIcon();

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
	initializedCounter = true;

	MountainLayer.restartLevel();
	SkyLayer.restartLevel();

	GameInfoLayer.SetCurrentLevel(level);
	GameInfoLayer.SetCurrentLifeBoss(30 / (TOTAL_LEVELS-level+1));
	GameInfoLayer.SetShowBossLife(false);

	// Load level
	res = Scene.LoadLevel(level);
	if (!res) return false;

	// Player initialization
	Player.SetTile(2, SCENE_HEIGHT / 2);
	Player.SetZ(SCENE_DEPTH);
	setPlayerSize();
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
				Scene.SetMapValue(i, j, 5 * TILE_SIZE, BICHO_HEIGHT, ENEMY_CIR - 48);
				Enemies.push_back(enemy);
			}
			else if (tile == BOSS) {
				Boss = new cBoss();
				Boss->SetTile(i, j);
				Boss->SetZ(SCENE_DEPTH);
				Boss->SetWidthHeight(2 * BICHO_WIDTH, 2 * BICHO_HEIGHT);
				Boss->SetWidthHeightProjectiles(20, 20);
				Scene.SetMapValue(i, j, 2 * BICHO_WIDTH, 2 * BICHO_HEIGHT, BOSS - 48);
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

	if (initializedCounter) {
		next_game_tick = GetTickCount();
		initializedCounter = false;
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

	if (currentPlayerID != DataManager.readPlayerIcon()) {
		currentPlayerID = DataManager.readPlayerIcon();
		setPlayerSize();
	}

	// Do not scroll if level is finished
	if (isGameStandBy() || isEndOfMap()) {
		SkyLayer.endOfLevel();
		MountainLayer.endOfLevel();
	}

	if (isBossInScene()) {
		GameInfoLayer.SetShowBossLife(true);
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
			Sound.PlayCustomSound(SOUND_CAT_SHOOT);
			keys[' '] = false;
		}

		if (keys['p'] || keys[27]) {
			gamePaused = true;
			keys['p'] = false;
			keys[27] = false;
		}

		float scroll = GAME_SCROLL;
		if (isEndOfMap()) {
			scroll = 0;
		}

		bool playerDead = false;

		//Game Logic
		Player.Logic(Scene.GetMap(), scroll);

		if (isPlayerOutsideWindow()) {
			playerDead = true;
		}

		Matrix map = Scene.GetMap();
		Player.LogicProjectiles(map);

		bool enemyHasShoot = false;
		for (int i = 0; i < Enemies.size(); ++i) {
			Enemies[i]->Logic(map, scroll);
			enemyHasShoot = Enemies[i]->LogicProjectiles(map, currentLevel, TOTAL_LEVELS) || enemyHasShoot;
		}
		if (enemyHasShoot) {
			//Sound.PlayCustomSound(SOUND_ENEMY_SHOOT);
		}

		Boss->Logic(map, scroll);
		bool bossHasShoot = Boss->LogicProjectiles(map, currentLevel, TOTAL_LEVELS);
		if (bossHasShoot) {
			Sound.PlayCustomSound(SOUND_BOSS_SHOOT);
		}

		Scene.SetMap(map);

		playerDead = playerDead || checkPlayerPosition();
		playerDead = playerDead || checkEnemiesProjectiles();
		playerDead = playerDead || checkBossProjectiles();

		bool enemyDead = checkPlayerProjectiles();
		if (enemyDead) {
			Sound.PlayCustomSound(SOUND_ENEMY_DEAD);
		}

		bool bossDead = checkBossDead();
		if (bossDead) {
			Sound.PlayCustomSound(SOUND_BOSS_DEAD);
		}

		bool projCollisions = checkProjectileCollisions();

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

	DrawMiniMap(Scene.GetMap());

	UpdateCameraScene();
	Scene.Draw(Data.GetID(IMG_SCENE));

	glColor3f(1.0f, 1.0f, 1.0f);

	Player.Draw(Data.GetID(Data.GetIMGPlayer(currentPlayerID)));
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

		if (!Enemies[i]->GetIsDead()) {
			Enemies[i]->Draw(tex_id_bicho);
		}
		else {
			Enemies[i]->Draw(Data.GetID(IMG_BURBUJA));
		}
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
	Boss->Draw(tex_id_boss);
	Boss->DrawProjectiles(Data.GetID(IMG_PROJ_BOSS));

	Player.DrawRainbow(Data.GetID(IMG_RAINBOW), cameraXScene);
	RestartCameraScene();

	GameInfoLayer.Draw();

	Sound.Update();

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

bool cGame::isBossInScene() {
	return cameraXScene <= Boss->GetX() && (Boss->GetX() - cameraXScene <= GAME_WIDTH);
}

void cGame::reinitializeRenderCounter() {
	initializedCounter = true;
}

void cGame::startSound(int sound) {
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

	glColor3f(0.2f, 0.2f, 0.2f);
	if (message == END_OF_LEVEL || message == GAME_PAUSED || message == LIFE_LOST) {
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
		Font.drawText(GAME_WIDTH / 2 - 150.0f, GAME_HEIGHT / 2 - 45.0f, MSS_DEPTH, 300.0f, 20.0f, message_second);
	}
	else {
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

bool cGame::checkBossDead() {
	bossDead = false;
	vector<Projectile> projsRight = Player.GetProjectiles(DIR_RIGHT);

	for (int p = 0; p < projsRight.size(); ++p) {
		float px = projsRight[p].x;
		float py = projsRight[p].y;

		if (Boss->GetX() <= px && px <= Boss->GetX() + Boss->GetWidth() &&
			Boss->GetY() <= py && py <= Boss->GetY() + Boss->GetHeight()) {
			//bossDead = true;
			
			int bossLife = GameInfoLayer.GetCurrentLifeBoss() - 1;
			GameInfoLayer.SetCurrentLifeBoss(bossLife);
			if (bossLife == 0) {
				bossDead = true;
				Boss->SetWidthHeight(0, 0);
			}

			projsRight.erase(projsRight.begin() + p);
		}
	}

	Player.SetProjectiles(projsRight, DIR_RIGHT);
	return bossDead;
}

bool cGame::checkPlayerPosition() {
	bool collides = false;

	for (int i = 0; i < Enemies.size() && !collides; ++i) {
		if (!Enemies[i]->GetIsDead()) {
			float enX = Enemies[i]->GetX();
			float enY = Enemies[i]->GetY();
			float enW = Enemies[i]->GetWidth();
			float enH = Enemies[i]->GetHeight();
			collides = checkPositionWithEnemy(enX, enY, enW, enH);
		}
	}

	if (!collides) {
		float enX = Boss->GetX();
		float enY = Boss->GetY();
		float enW = Boss->GetWidth();
		float enH = Boss->GetHeight();
		collides = checkPositionWithEnemy(enX, enY, enW, enH);
	}

	return collides;
}

bool cGame::checkPositionWithEnemy(float enX, float enY, int enW, int enH) {
	float xPlayer = Player.GetX();
	float yPlayer = Player.GetY();
	int wPlayer = Player.GetWidth();
	int hPlayer = Player.GetHeight();

	bool notCollision = false;
	if (enY + enH < yPlayer || yPlayer + hPlayer < enY) notCollision = true;
	if (enX + enW < xPlayer || xPlayer + wPlayer < enX) notCollision = true;

	return (!notCollision);
}

bool cGame::checkPlayerProjectiles() {
	vector<Projectile> projsRight = Player.GetProjectiles(DIR_RIGHT);
	bool hitSomeEnemies = false;
	int wP = Player.GetWProj();
	int hP = Player.GetHProj();

	for (int p = 0; p < projsRight.size(); ++p) {
		float xP = projsRight[p].x;
		float yP = projsRight[p].y;

		bool found = false;
		for (int v = 0; v < Enemies.size() && !found; ++v) {
			if (!Enemies[v]->GetIsDead()) {
				float xE = Enemies[v]->GetX();
				float yE = Enemies[v]->GetY();
				int wE = Enemies[v]->GetWidth();
				int hE = Enemies[v]->GetHeight();

				bool notCollision = false;
				if (yE + hE < yP || yP + hP < yE) notCollision = true;
				if (xE + wE < xP || xP + wP < xE) notCollision = true;

				bool collision = !notCollision;

				if (collision) {
					found = true;
					hitSomeEnemies = true;
					Enemies[v]->SetIsDead(true);
					projsRight.erase(projsRight.begin() + p);

					int txE = xE / TILE_SIZE;
					int tyE = yE / TILE_SIZE;

					Scene.SetMapValue(txE, tyE, Enemies[v]->GetWidth(), Enemies[v]->GetHeight(), EMPTY);

					GameInfoLayer.SetCurrentScore(GameInfoLayer.GetCurrentScore() + 1);
				}
			}
		}
	}
	
	Player.SetProjectiles(projsRight, DIR_RIGHT);
	return hitSomeEnemies;
}

bool cGame::checkEnemiesProjectiles() {
	bool collides = false;
	for (int i = 0; i < Enemies.size() && !collides; ++i) {
		collides = checkProjectilesEnemy(Enemies[i]->GetProjectiles(DIR_RIGHT), Enemies[i]->GetWProj(), Enemies[i]->GetHProj());
		collides = collides || checkProjectilesEnemy(Enemies[i]->GetProjectiles(DIR_LEFT), Enemies[i]->GetWProj(), Enemies[i]->GetHProj());
	}

	return collides;
}

bool cGame::checkBossProjectiles() {
	bool collides = checkProjectilesEnemy(Boss->GetProjectiles(DIR_LEFT), Boss->GetWProj(), Boss->GetHProj());

	return collides;
}

bool cGame::checkProjectilesEnemy(vector<Projectile>& projs, int wE, int hE) {
	float xP = Player.GetX();
	float yP = Player.GetY();
	int wP = Player.GetWidth();
	int hP = Player.GetHeight();

	for (int p = 0; p < projs.size(); ++p) {
		float xE = projs[p].x;
		float yE = projs[p].y;

		bool notCollision = false;
		if (yE + hE < yP || yP + hP < yE) notCollision = true;
		if (xE + wE < xP || xP + wP < xE) notCollision = true;

		bool collision = !notCollision;
		if (collision) return true;
	}
	return false;
}

void cGame::setPlayerSize() {
	if (Data.GetIMGPlayer(currentPlayerID) == IMG_MEXICAN) {
		Player.SetWidthHeight(4 * TILE_SIZE, 3 * TILE_SIZE);
	}
	else if (Data.GetIMGPlayer(currentPlayerID) == IMG_OKTOBER) {
		Player.SetWidthHeight(3 * TILE_SIZE, 3 * TILE_SIZE);
	}
	else {
		Player.SetWidthHeight(BICHO_WIDTH, BICHO_HEIGHT);
	}
}

void cGame::DrawMiniMap(Matrix &map) {
	float size = 1.0f;
	float pxo = 10.0f;
	float pyo = 2.0f;

	float px, py, w, h;
	float pxmid1 = cameraXScene;
	float pxmid2 = cameraXScene + GAME_WIDTH;

	float pxini = pxo - size*2;
	float pxfi = pxini + size*2 + SCENE_WIDTH*size + size * 2;
	float pyini = pyo;
	float pyfi = pyini + SCENE_HEIGHT*size + size * 2;

	// Margen negro
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3i(pxini, pyini, GAMEINFO_DEPTH - 2);
	glVertex3i(pxfi, pyini, GAMEINFO_DEPTH - 2);
	glVertex3i(pxfi, pyfi, GAMEINFO_DEPTH - 2);
	glVertex3i(pxini, pyfi, GAMEINFO_DEPTH - 2);
	glEnd();

	// Region Izquierda gris
	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_QUADS);
	glVertex3i(pxo, pyo + 2*size, GAMEINFO_DEPTH);
	glVertex3i(pxo + max(0,floor(pxmid1 / TILE_SIZE * size)-2*size), pyo + 2 * size, GAMEINFO_DEPTH);
	glVertex3i(pxo + max(0, floor(pxmid1 / TILE_SIZE * size)-2*size), pyo + size * SCENE_HEIGHT, GAMEINFO_DEPTH);
	glVertex3i(pxo, pyo + size * SCENE_HEIGHT, GAMEINFO_DEPTH);
	glEnd();

	// Region fondo visto
	glColor3f(0.3f, 0.4f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3i(pxo + floor(pxmid1 / TILE_SIZE) * size, pyo + 2 * size, GAMEINFO_DEPTH-1);
	glVertex3i(pxo + ceil(pxmid2 / TILE_SIZE) * size + size, pyo + 2 * size, GAMEINFO_DEPTH-1);
	glVertex3i(pxo + ceil(pxmid2 / TILE_SIZE) * size + size, pyo + size * SCENE_HEIGHT, GAMEINFO_DEPTH-1);
	glVertex3i(pxo + floor(pxmid1 / TILE_SIZE) * size, pyo + size * SCENE_HEIGHT, GAMEINFO_DEPTH-1);
	glEnd();

	// Escena vista
	glColor3f(0.2f, 0.2f, 0.2f);
	px = pxo + pxmid1 / TILE_SIZE * size;
	for (int tx = floor(pxmid1 / TILE_SIZE); tx <= min(ceil(pxmid2 / TILE_SIZE), SCENE_WIDTH-1); ++tx) {
		for (int ty = SCENE_HEIGHT - 1; ty >= 2; --ty) {
			py = pyo + ty*size;

			if (Scene.isScene(tx, ty)) {
				glBegin(GL_QUADS);
				glVertex3i(px, py, GAMEINFO_DEPTH);
				glVertex3i(px + size, py, GAMEINFO_DEPTH);
				glVertex3i(px + size, py + size, GAMEINFO_DEPTH);
				glVertex3i(px, py + size, GAMEINFO_DEPTH);
				glEnd();
			}
		}

		px += size;
	}

	// Region Derecha gris
	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_QUADS);
	glVertex3i(pxo + size * 3 + ceil(pxmid2 / TILE_SIZE) * size, pyo + 2 * size, GAMEINFO_DEPTH);
	glVertex3i(pxo + SCENE_WIDTH * size, pyo + 2 * size, GAMEINFO_DEPTH);
	glVertex3i(pxo + SCENE_WIDTH * size, pyo + size * SCENE_HEIGHT, GAMEINFO_DEPTH);
	glVertex3i(pxo + size * 3 + ceil(pxmid2 / TILE_SIZE) * size, pyo + size * SCENE_HEIGHT, GAMEINFO_DEPTH);
	glEnd();

	float xmin = pxo + floor(pxmid1 / TILE_SIZE) * size;
	float xmax = pxo + ceil(pxmid2 / TILE_SIZE) * size + size;

	// Enemigos rojos
	glColor3f(1.0f,0.0f,0.0f);
	for (int i = 0; i < Enemies.size(); ++i) {
		if (!Enemies[i]->GetIsDead()) {
			px = pxo + Enemies[i]->GetX() / TILE_SIZE * size;
			py = pyo + Enemies[i]->GetY() / TILE_SIZE * size;
			w = Enemies[i]->GetWidth() / TILE_SIZE * size;
			h = Enemies[i]->GetHeight() / TILE_SIZE * size;
			DrawRect(px, py, GAMEINFO_DEPTH, w, h, xmin, xmax);
		}
	}

	// Player cyan
	px = pxo + Player.GetX() / TILE_SIZE * size;
	py = pyo + Player.GetY() / TILE_SIZE * size;
	w = Player.GetWidth() / TILE_SIZE * size;
	h = Player.GetHeight() / TILE_SIZE * size;
	glColor3f(0.0f, 1.0f, 1.0f);
	DrawRect(px, py, GAMEINFO_DEPTH, w, h, xmin, xmax);

	// Boss amarillo
	px = pxo + Boss->GetX() / TILE_SIZE * size;
	py = pyo + Boss->GetY() / TILE_SIZE * size;
	w = Boss->GetWidth() / TILE_SIZE * size;
	h = Boss->GetHeight() / TILE_SIZE * size;
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawRect(px, py, GAMEINFO_DEPTH, w, h, xmin, xmax);

	glColor3f(1.0f, 1.0f, 1.0f);
}

void cGame::DrawRect(float x, float y, float z, int w, int h, float xmin, float xmax) {
	if (x + w>= xmin && x <= xmax) {
		glBegin(GL_QUADS);
		glVertex3i(max(x, xmin), y, z);
		glVertex3i(min(x + w, xmax), y, z);
		glVertex3i(min(x + w, xmax), y + h, z);
		glVertex3i(max(x, xmin), y + h, z);
		glEnd();
	}
}

bool cGame::checkProjectileCollisions() {
	bool collides = false;

	collides = collides || checkProjectileCollisions(DIR_LEFT);
	collides = collides || checkProjectileCollisions(DIR_RIGHT);

	return collides;
}

bool cGame::checkProjectileCollisions(int dir) {
	bool collides = false;
	vector<Projectile> projP = Player.GetProjectiles(dir);

	for (int i = 0; i < Enemies.size(); ++i) {
		vector<Projectile> projE = Enemies[i]->GetProjectiles(-dir);
		int wE = Enemies[i]->GetWProj();
		int hE = Enemies[i]->GetHProj();
		vector<Projectile> projE2 = collisionProjectiles(projP, dir, projE, wE, hE);
		Enemies[i]->SetProjectiles(projE2,-dir);
		if (projE2.size() != projE.size()) collides = true;
	}

	vector<Projectile> projB = Boss->GetProjectiles(-dir);
	int wB = Boss->GetWProj();
	int hB = Boss->GetHProj();
	vector<Projectile> projB2 = collisionProjectiles(projP, dir, projB, wB, hB);
	Boss->SetProjectiles(projB2, -dir);
	if (projB2.size() != projB.size()) collides = true;

	return collides;
}

vector<Projectile> cGame::collisionProjectiles(vector<Projectile>& projP, int dir, vector<Projectile>& projE, int wE, int hE) {
	bool collides = false;
	int wP = Player.GetWProj();
	int hP = Player.GetHProj();

	for (int i = 0; i < projP.size(); ++i) {
		float xP = projP[i].x;
		float yP = projP[i].y;

		bool collision = false;
		for (int j = 0; j < projE.size() && !collision; ++j) {
			float xE = projE[j].x;
			float yE = projE[j].y;

			bool notCollision = false;
			if (yE + hE < yP || yP + hP < yE) notCollision = true;
			if (xE + wE < xP || xP + wP < xE) notCollision = true;

			collision = !notCollision;

			if (collision) {
				OutputDebugStringA("Collision!\n");
				projP.erase(projP.begin() + i);
				projE.erase(projE.begin() + j);
			}
		}
	}

	Player.SetProjectiles(projP, dir);

	return projE;
}