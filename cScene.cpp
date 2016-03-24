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
	float coordxo_tile, coordxf_tile, coordyo_tile, coordyf_tile;

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
			else if (tile == ENEMY_HOR || tile == ENEMY_VER || tile == ENEMY_CIR || tile == 'z') {
				map[j][i] = 0;
			}
			else {
				map[j][i] = tile - 48;

				switch (map[j][i]) {
					case GROUND:
						coordxo_tile = 0.0f;
						coordxf_tile = 0.1f;
						break;
					case CLOUD_SUP_ESQ:
					case CLOUD_INF_ESQ:
						coordxo_tile = 0.0f;
						coordxf_tile = 0.33f;
						break;
					case CLOUD_SUP_CEN:
					case CLOUD_INF_CEN:
						coordxo_tile = 0.33f;
						coordxf_tile = 0.67f;
						break;
					case CLOUD_SUP_DRE:
					case CLOUD_INF_DRE:
						coordxo_tile = 0.67f;
						coordxf_tile = 1.0f;
						break;
				}

				switch (map[j][i]) {
					case GROUND:
						coordyo_tile = 0.0f;
						coordyf_tile = 0.25f;
						break;
					case CLOUD_SUP_ESQ:
					case CLOUD_SUP_CEN:
					case CLOUD_SUP_DRE:
						coordyo_tile = 0.5f;
						coordyf_tile = 0.75f;
						break;
					case CLOUD_INF_ESQ:
					case CLOUD_INF_CEN:
					case CLOUD_INF_DRE:
						coordyo_tile = 0.75f;
						coordyf_tile = 1.0f;
						break;
				}

				if (map[j][i] == GROUND) glColor3f(1.0f, 1.0f, 1.0f);
				else glColor3f(0.8f, 0.8f, 1.0f);

				glTexCoord2f(coordxo_tile, coordyf_tile);	glVertex3i(px, py, SCENE_DEPTH);
				glTexCoord2f(coordxf_tile, coordyf_tile);	glVertex3i(px + TILE_SIZE, py, SCENE_DEPTH);
				glTexCoord2f(coordxf_tile, coordyo_tile);	glVertex3i(px + TILE_SIZE, py + TILE_SIZE, SCENE_DEPTH);
				glTexCoord2f(coordxo_tile, coordyo_tile);	glVertex3i(px, py + TILE_SIZE, SCENE_DEPTH);
			}
			px += TILE_SIZE;
		}
		fscanf(fd, "%c", &tile); //pass enter
	}

	glEnd();
	glEndList();

	glColor3f(1.0f, 1.0f, 1.0f);

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

void cScene::SetMap(Matrix &mapa) {
	map = mapa;
}

bool cScene::endOfMap(float cameraX) {
	if (cameraX + GAME_WIDTH >= SCENE_WIDTH * TILE_SIZE) return true;
	return false;
}