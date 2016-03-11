#include "cScene.h"
#include "Globals.h"
#include <windows.h>

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
	char file[16];
	int i, j, px, py;
	char tile;
	float coordx_tile, coordy_tile;

	res = true;

	string scene_path;
	if (level == 1) scene_path = LEVELS_FOLDER "/" FILENAME "1" FILENAME_EXT;
	else if (level == 2) scene_path = LEVELS_FOLDER "/" FILENAME "2" FILENAME_EXT;
	else if (level == 3) scene_path = LEVELS_FOLDER "/" FILENAME "3" FILENAME_EXT;

	fd = fopen(scene_path.c_str(), "r");
	if (fd == NULL) return false;

	id_DL = glGenLists(1);
	glNewList(id_DL, GL_COMPILE);
	glBegin(GL_QUADS);

	for (j = SCENE_HEIGHT - 1; j >= 0; j--)
	{
		px = 0;
		py = j*TILE_SIZE;

		for (i = 0; i<SCENE_WIDTH; i++)
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
				if (map[(j*SCENE_WIDTH) + i]<3) coordy_tile = 0.0f;
				else						 coordy_tile = 0.5f;

				//BLOCK_SIZE = 24, FILE_SIZE = 64
				// 24 / 64 = 0.375
				glTexCoord2f(coordx_tile, coordy_tile + 0.5f);	glVertex3i(px, py, DEPTH);
				glTexCoord2f(coordx_tile + 0.5f, coordy_tile + 0.5f);	glVertex3i(px + TILE_SIZE, py, DEPTH);
				glTexCoord2f(coordx_tile + 0.5f, coordy_tile);	glVertex3i(px + TILE_SIZE, py + TILE_SIZE, DEPTH);
				glTexCoord2f(coordx_tile, coordy_tile);	glVertex3i(px, py + TILE_SIZE, DEPTH);
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