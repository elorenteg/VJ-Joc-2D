#include "cFont.h"

//http://www.andrewewhite.net/wordpress/2007/06/06/very-simple-text-in-opengl/

cFont::cFont(void) {}

void cFont::setFont(int init_texture, int init_m_width, int init_m_height,
	int init_c_width, int init_c_height) {

	texture = init_texture;
	// bitmap size
	m_width = init_m_width;
	m_height = init_m_height;
	// character size
	c_width = init_c_width;
	c_height = init_c_height;

	c_per_row = m_width / c_width;
}

void cFont::drawText(float x, float y, float z, int w, int h, char * text) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTranslatef(x, y, 0.0f);

	glBegin(GL_QUADS);
		//character location and dimensions
		float cx = 0.0f;
		float cy = 0.0f;
		float cw = float(w) / strlen(text);
		float ch = float(h);

		//calculate how wide each character is in term of texture coords
		float dtx = float(c_width) / float(m_width);
		float dty = float(c_height) / float(m_height);
		
		for (int i = 0; i < strlen(text); ++i) {
			char c = text[i];

			// subtract the value of the first char in the character map to get the index in our map
			int index = c - '0';
			int row = index / c_per_row;
			int col = index%c_per_row;

			// find the texture coords
			float tx = float(col * c_width) / float(m_width);
			float ty = float(row * c_height) / float(m_height);

			glTexCoord2d(tx, ty + dty); glVertex3f(cx, cy, z);
			glTexCoord2d(tx + dtx, ty + dty); glVertex3f(cx + cw, cy, z);
			glTexCoord2d(tx + dtx, ty); glVertex3f(cx + cw, cy + ch, z);
			glTexCoord2d(tx, ty); glVertex3f(cx, cy + ch, z);

			cx += cw;
		}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glPopMatrix();
}