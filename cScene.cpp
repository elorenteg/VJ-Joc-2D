#include "cScene.h"
#include "Globals.h"

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

bool cScene::LoadLevel(int level)
{
	bool res;
	FILE *fd;
	char file[32];
	int i, j, px, py;
	char tile;
	float coordx_tile, coordy_tile;

	res = true;

	if (level < 10) sprintf(file, "%s/%s0%d%s", (char *)LEVELS_FOLDER, (char *)FILENAME, level, (char *)FILENAME_EXT);
	else		 sprintf(file, "%s/%s%d%s", (char *)LEVELS_FOLDER, (char *)FILENAME, level, (char *)FILENAME_EXT);

	fd = fopen(file, "r");
	if (fd == NULL) return false;

	id_DL = glGenLists(1);
	glNewList(id_DL, GL_COMPILE);
	glBegin(GL_QUADS);

	for (j = SCENE_HEIGHT - 1; j >= 0; j--)
	{
		px = SCENE_Xo;
		py = SCENE_Yo + (j*TILE_SIZE);

		for (i = 0; i < SCENE_WIDTH; i++)
		{
			fscanf(fd, "%c", &tile);
			if (tile == ' ')
			{
				//Tiles must be != 0 !!!
				map[(j*SCENE_WIDTH) + i] = 0;
			}
			else
			{
				//Tiles = 1,2,3,...
				map[(j*SCENE_WIDTH) + i] = tile - 48;

				if (map[(j*SCENE_WIDTH) + i] % 2) coordx_tile = 0.0f;
				else						 coordx_tile = 0.5f;
				if (map[(j*SCENE_WIDTH) + i] < 3) coordy_tile = 0.0f;
				else						 coordy_tile = 0.5f;

				//BLOCK_SIZE = 24, FILE_SIZE = 64
				// 24 / 64 = 0.375
				glTexCoord2f(coordx_tile, coordy_tile + 0.375f);	glVertex2i(px, py);
				glTexCoord2f(coordx_tile + 0.375f, coordy_tile + 0.375f);	glVertex2i(px + BLOCK_SIZE, py);
				glTexCoord2f(coordx_tile + 0.375f, coordy_tile);	glVertex2i(px + BLOCK_SIZE, py + BLOCK_SIZE);
				glTexCoord2f(coordx_tile, coordy_tile);	glVertex2i(px, py + BLOCK_SIZE);
			}
			px += TILE_SIZE;
		}
		fscanf(fd, "%c", &tile); //pass enter
	}

	glEnd();
	glEndList();

	fclose(fd);

	return res;
}

bool cScene::LoadBackground(int level)
{
	bool res;

	res = true;

	id_DL = glGenLists(1);
	glNewList(id_DL, GL_COMPILE);

	//glTranslatef(-GAME_WIDTH / 2, -GAME_HEIGHT / 2, 0);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1.0f); glVertex2i(0, 0);
	glTexCoord2i(1, 1.0f); glVertex2i(GAME_WIDTH, 0);
	glTexCoord2i(1, 0.0f); glVertex2i(GAME_WIDTH, GAME_HEIGHT);
	glTexCoord2i(0, 0.0f); glVertex2i(0, GAME_HEIGHT);
	glEnd();

	glEndList();

	return res;
}

void cScene::Draw(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}
int* cScene::GetMap()
{
	return map;
}