#include "Spacebox.hpp"

Spacebox::Spacebox(int size, Texture * side1) {
	this->side_len = size;

	// Assign textures to sides
	textures[0] = side1;
}

Spacebox::~Spacebox() {

}

void Spacebox::apply_textures() {

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, this->textures[0]->get_texture());

}

/*

Src: https://www.opengl.org/discussion_boards/showthread.php/134414-Outer-space-skybox-textures

*/
void Spacebox::draw_skybox() {

	glMatrixMode(GL_PROJECTION);
    glPushMatrix();

	gluPerspective(90, 1.0, 1.0, 1.0);
	glPushMatrix();

	float m[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, m[0]);
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0;
	glLoadMatrixf(m[0]);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(0);

	glEnable(GL_TEXTURE_2D);
	

		apply_textures();
		draw_face();

	glDisable(GL_TEXTURE_2D);


	glDepthMask(1);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


}

void Spacebox::draw_face() {

		glBindTexture(GL_TEXTURE_2D, textures[0]->get_texture());
		glBegin(GL_QUADS);

		glTexCoord2d(0.0f, 1.0f);	glVertex3f(side_len, -side_len, -side_len);	// Bottom Left Of The Quad (Back)
		glTexCoord2d(1.0f, 1.0f);	glVertex3f(-side_len, -side_len, -side_len);	// Bottom Right Of The Quad (Back)
		glTexCoord2d(1.0f, 0.0f);	glVertex3f(-side_len, side_len, -side_len);	// Top Right Of The Quad (Back)
		glTexCoord2d(0.0f, 0.0f);	glVertex3f(side_len, side_len, -side_len);	// Top Left Of The Quad (Back)

		glEnd();	
}