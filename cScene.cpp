#include "cScene.h"

cScene::cScene(void) {
	map = Matrix(SCENE_HEIGHT, vector<int>(SCENE_WIDTH));
}

cScene::~cScene(void) {
}

bool cScene::LoadLevel(int level) {
	bool res;
	FILE *fd;
	int i, j, px, py;
	char tile;
	float coordx_tile, coordy_tile;

	res = true;

	string scene_path;
	if (level == 1) scene_path = LEVELS_FOLDER "/" FILENAME "1" FILENAME_EXT;
	else if (level == 2) scene_path = LEVELS_FOLDER "/" FILENAME "2" FILENAME_EXT;
	else if (level == 3) scene_path = LEVELS_FOLDER "/" FILENAME "3" FILENAME_EXT;
	else if (level == 10) scene_path = LEVELS_FOLDER "/" FILENAME "10" FILENAME_EXT;

	fd = fopen(scene_path.c_str(), "r");
	if (fd == NULL) return false;

	id_DL = glGenLists(1);
	glNewList(id_DL, GL_COMPILE);
	glBegin(GL_QUADS);

	for (j = SCENE_HEIGHT - 1; j >= 0; j--) {
		px = 0;
		py = j*TILE_SIZE;

		for (i = 0; i<SCENE_WIDTH; i++) {
			fscanf(fd, "%c", &tile);
			if (tile == ' ') {
				map[j][i] = 0;
			}
			else {
				map[j][i] = tile - 48;

				if (map[j][i] % 2) coordx_tile = 0.0f;
				else coordx_tile = 0.5f;

				if (map[j][i]<3) coordy_tile = 0.0f;
				else coordy_tile = 0.5f;

				glTexCoord2f(coordx_tile, coordy_tile + 0.5f);			glVertex3i(px, py, DEPTH);
				glTexCoord2f(coordx_tile + 0.5f, coordy_tile + 0.5f);	glVertex3i(px + TILE_SIZE, py, DEPTH);
				glTexCoord2f(coordx_tile + 0.5f, coordy_tile);			glVertex3i(px + TILE_SIZE, py + TILE_SIZE, DEPTH);
				glTexCoord2f(coordx_tile, coordy_tile);					glVertex3i(px, py + TILE_SIZE, DEPTH);
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

void cScene::Draw(int tex_id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}

Matrix cScene::GetMap() {
	return map;
}

bool cScene::endOfMap(float cameraX) {
	if (cameraX + GAME_WIDTH >= SCENE_WIDTH * TILE_SIZE) return true;
	return false;
}