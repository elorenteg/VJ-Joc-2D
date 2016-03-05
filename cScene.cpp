#include "cScene.h"
#include "Globals.h"

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

bool cScene::LoadBackground(int level)
{
	bool res;

	res = true;

	id_DL_Background = glGenLists(1);
	glNewList(id_DL_Background, GL_COMPILE);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
	glTexCoord2f(2.5f, 1.0f); glVertex2i(GAME_WIDTH, 0);
	glTexCoord2f(2.5f, 0.0f); glVertex2i(GAME_WIDTH, GAME_HEIGHT);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, GAME_HEIGHT);
	glEnd();

	glEndList();

	return res;
}

bool cScene::LoadLayer2(int level)
{
	bool res;

	res = true;

	id_DL_Layer2 = glGenLists(1);
	glNewList(id_DL_Layer2, GL_COMPILE);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
	glTexCoord2f(2.5f, 1.0f); glVertex2i(GAME_WIDTH, 0);
	glTexCoord2f(2.5f, 0.0f); glVertex2i(GAME_WIDTH, GAME_HEIGHT/2);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, GAME_HEIGHT/2);
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

void cScene::setDisplayList(int id) {
	if (id == 1) id_DL = id_DL_Background;
	else id_DL = id_DL_Layer2;
}