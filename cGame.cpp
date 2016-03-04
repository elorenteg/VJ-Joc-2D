#include "cGame.h"
#include "Globals.h"

//http://www.koonsolo.com/news/dewitters-gameloop/
const int FRAMES_PER_SECOND = 70;
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

// Returns the current number of ms elapsed since the system was started
DWORD next_game_tick = GetTickCount();

int sleep_time = 0;
bool game_is_running = true;

cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res = true;

	//Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	char scene_path[64];
	strcpy(scene_path, IMAGES_FOLDER);
	strcat(scene_path, "/");
	strcat(scene_path, "blocks.png");
	res = Data.LoadImage(IMG_BLOCKS, scene_path, GL_RGBA);
	if (!res) return false;
	res = Scene.LoadLevel(1);
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

	glLoadIdentity();

	Scene.Draw(Data.GetID(IMG_BLOCKS));
	Player.Draw(Data.GetID(IMG_PLAYER));

	glutSwapBuffers();
}
