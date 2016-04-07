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

	id_DL = glGenLists(1);
	glNewList(id_DL, GL_COMPILE);
	glBegin(GL_QUADS);

	for (j = SCENE_HEIGHT - 1; j >= 0; j--) {
		px = 0;
		py = j*TILE_SIZE;

		for (i = 0; i<SCENE_WIDTH; i++) {
			fscanf(fd, "%c", &tile);
			if (tile == ' ' || tile == ENEMY_HOR || tile == ENEMY_VER || tile == ENEMY_CIR || tile == BOSS || tile == RESERVED) {
				map[j][i] = EMPTY;
			}
			else {
				map[j][i] = tile - 48;

				switch (map[j][i]) {
					case GROUND:
					case GRASS:
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
						coordyo_tile = 0.2f;
						coordyf_tile = 0.4f;
						break;
					case GRASS:
						coordyo_tile = 0.0f;
						coordyf_tile = 0.2f;
						break;
					case CLOUD_SUP_ESQ:
					case CLOUD_SUP_CEN:
					case CLOUD_SUP_DRE:
						coordyo_tile = 0.4f;
						coordyf_tile = 0.6f;
						break;
					case CLOUD_INF_ESQ:
					case CLOUD_INF_CEN:
					case CLOUD_INF_DRE:
						coordyo_tile = 0.6f;
						coordyf_tile = 0.8f;
						break;
				}

				if (map[j][i] == GROUND || map[j][i] == GRASS) glColor3f(1.0f, 1.0f, 1.0f);
				else glColor3f(0.9f, 0.9f, 1.0f);

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

void cScene::SetMapValue(int tile_x, int tile_y, int width, int height, int value) {
	for (int i = tile_x; i < tile_x + width / TILE_SIZE; ++i) {
		for (int j = tile_y; j < tile_y + height / TILE_SIZE; ++j) {
			map[j][i] = value;

			char msgbuf[128];
			sprintf(msgbuf, "map=%d -- %d,%d\n", map[j][i], i,j);
			OutputDebugStringA(msgbuf);
		}
	}
}

bool cScene::isEnemy(int tile_x, int tile_y) {
	if (map[tile_y][tile_x] == ENEMY_VER - 48) return true;
	if (map[tile_y][tile_x] == ENEMY_HOR - 48) return true;
	if (map[tile_y][tile_x] == ENEMY_CIR - 48) return true;
	return false;
}

bool cScene::isScene(int tile_x, int tile_y) {
	if (map[tile_y][tile_x] == GROUND) return true;
	if (map[tile_y][tile_x] == GRASS) return true;
	if (map[tile_y][tile_x] == CLOUD_SUP_ESQ) return true;
	if (map[tile_y][tile_x] == CLOUD_SUP_CEN) return true;
	if (map[tile_y][tile_x] == CLOUD_SUP_DRE) return true;
	if (map[tile_y][tile_x] == CLOUD_INF_ESQ) return true;
	if (map[tile_y][tile_x] == CLOUD_INF_CEN) return true;
	if (map[tile_y][tile_x] == CLOUD_INF_DRE) return true;
	return false;
}

bool cScene::isBoss(int tile_x, int tile_y) {
	if (map[tile_y][tile_x] == BOSS - 48) return true;
	return false;
}

