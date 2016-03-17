#include "cGame.h"
#include "Globals.h"

cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res = true;
	cameraXScene = 0;

	//Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	strcat(scene_path, "blocks.png");
	res = Data.LoadImage(IMG_BLOCKS, scene_path, GL_RGBA);
	if (!res) return false;
	res = Scene.LoadLevel(10);
	if (!res) return false;

	//Player initialization
	char player_path[64];
	strcpy(player_path, IMAGES_FOLDER);
	strcat(player_path, "/");
	strcat(player_path, "bub.png");
	res = Data.LoadImage(IMG_PLAYER, player_path, GL_RGBA);
	if (!res) return false;
	Player.SetWidthHeight(32, 32);
	Player.SetTile(4, 1);
	Player.SetWidthHeight(32, 32);
	Player.SetState(STATE_LOOKRIGHT);

	return res;
}

bool cGame::Loop()
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

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res = true;

	//Process Input
	if (keys[27])	res = false;

	if (keys[GLUT_KEY_UP])
		Player.Jump(Scene.GetMap());
	if (keys[GLUT_KEY_LEFT])
		Player.MoveLeft(Scene.GetMap());
	else if (keys[GLUT_KEY_RIGHT])
		Player.MoveRight(Scene.GetMap());
	else Player.Stop();

	//Game Logic
	Player.Logic(Scene.GetMap());

	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// If end of game, map do not scroll
	if (Scene.endOfMap(cameraXScene)) {
		SkyLayer.endOfGame();
		MountainLayer.endOfGame();
	}

	SkyLayer.Draw(Data.GetID(IMG_BACKGROUND));
	MountainLayer.Draw(Data.GetID(IMG_LAYER2));

	UpdateCameraScene();
	Scene.Draw(Data.GetID(IMG_BLOCKS));
	RestartCameraScene();

	Player.Draw(Data.GetID(IMG_PLAYER));

	glutSwapBuffers();
}

void cGame::UpdateCameraScene() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(cameraXScene, cameraXScene + GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);

	// If not end of game, map can continue scrolling
	if (!Scene.endOfMap(cameraXScene)) cameraXScene += 0.2f;
}

void cGame::RestartCameraScene() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 0 + GAME_WIDTH, 0, GAME_HEIGHT, 0, GAME_DEPTH);
	glMatrixMode(GL_MODELVIEW);
}
