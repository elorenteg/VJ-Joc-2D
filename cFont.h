#pragma once

#include "cData.h"
#include "Globals.h"

class cFont
{
public:
	cFont(void);

	void setFont(int init_texture, int init_m_width, int init_m_height, int init_c_width, int init_c_height);
	void drawText(float x, float y, int w, int h, char * text);

private:
	int texture;
	int c_per_row;

	//bitmap setting
	int m_width;
	int m_height;

	//character settings
	int c_width;
	int c_height;
};