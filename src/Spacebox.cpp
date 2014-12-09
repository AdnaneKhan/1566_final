#include "Spacebox.hpp"

Spacebox::Spacebox(int size, Texture * side1, Texture *side2, Texture* side3, Texture *side4, Texture *side5, Texture* side6) {
	this->side_len = size;

	// Assign textures to sides
	textures[0] = side1;
	textures[1] = side2;
	textures[2] = side3;
	textures[3] = side4;
	textures[4] = side5;
	textures[5] = side6;

}

Spacebox::~Spacebox() {

}

void Spacebox::apply_textures(int face_num) {

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, this->textures[face_num]->get_texture());

}

/*


Src: https://www.opengl.org/discussion_boards/showthread.php/134414-Outer-space-skybox-textures

*/
void Spacebox::draw_skybox(GLfloat position[3]) {
	glPushMatrix();

	float m[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, m[0]);
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0;
	glLoadMatrixf(m[0]);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(0);

	glEnable(GL_TEXTURE_2D);
	
	for (int i = 0; i < 5; i++) {

		apply_textures(i);
		draw_face(i);
	}
	glDisable(GL_TEXTURE_2D);


	glDepthMask(1);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();


}

void Spacebox::draw_face(int face_num) {
	switch (face_num) {
	case TOP: 
		glBindTexture(GL_TEXTURE_2D, textures[face_num]->get_texture());
		glBegin(GL_QUADS);

		glTexCoord2d(1.0f, 0.0f);	glVertex3f(side_len, side_len, -side_len);	// Top Right Of The Quad (Top)
		glTexCoord2d(1.0f, 1.0f);	glVertex3f(-side_len, side_len, -side_len);	// Top Left Of The Quad (Top)
		glTexCoord2d(0.0, 1.0f);	glVertex3f(-side_len, side_len, side_len);	// Bottom Left Of The Quad (Top)
		glTexCoord2d(0.0, 0.0f);	glVertex3f(side_len, side_len, side_len);	// Bottom Right Of The Quad (Top)
		glEnd();

		break;
	case FRONT:
		glBindTexture(GL_TEXTURE_2D, textures[face_num]->get_texture());
		glBegin(GL_QUADS);

		glTexCoord2d(0.0f, 0.0f);	glVertex3f(side_len, side_len, side_len);	// Top Right Of The Quad (Front)
		glTexCoord2d(1.0f, 0.0f);	glVertex3f(-side_len, side_len, side_len);	// Top Left Of The Quad (Front)
		glTexCoord2d(1.0f, 1.0f);	glVertex3f(-side_len, -side_len, side_len);	// Bottom Left Of The Quad (Front)
		glTexCoord2d(0.0f, 1.0f);	glVertex3f(side_len, -side_len, side_len);	// Bottom Right Of The Quad (Front)

		glEnd();


		break;
	case BACK:

		glBindTexture(GL_TEXTURE_2D, textures[face_num]->get_texture());
		glBegin(GL_QUADS);

		glTexCoord2d(0.0f, 1.0f);	glVertex3f(side_len, -side_len, -side_len);	// Bottom Left Of The Quad (Back)
		glTexCoord2d(1.0f, 1.0f);	glVertex3f(-side_len, -side_len, -side_len);	// Bottom Right Of The Quad (Back)
		glTexCoord2d(1.0f, 0.0f);	glVertex3f(-side_len, side_len, -side_len);	// Top Right Of The Quad (Back)
		glTexCoord2d(0.0f, 0.0f);	glVertex3f(side_len, side_len, -side_len);	// Top Left Of The Quad (Back)

		glEnd();

		break;
	case LEFT:
		glBindTexture(GL_TEXTURE_2D, textures[face_num]->get_texture());
		glBegin(GL_QUADS);
		glTexCoord2d(1.0f, 0.0f);	glVertex3f(-side_len, side_len, -side_len);	// Top Right Of The Quad (Left)
		glTexCoord2d(1.0f, 1.0f);	glVertex3f(-side_len, -side_len, -side_len);	// Top Left Of The Quad (Left)
		glTexCoord2d(0.0f, 1.0f);	glVertex3f(-side_len, -side_len, side_len);	// Bottom Left Of The Quad (Left)
		glTexCoord2d(0.0f, 0.0f);	glVertex3f(-side_len, side_len, side_len);	// Bottom Right Of The Quad (Left)


		glEnd();

		break;
	case RIGHT:
		glBindTexture(GL_TEXTURE_2D, textures[face_num]->get_texture());
		glBegin(GL_QUADS);

		glTexCoord2d(0.0f, 0.0f);	glVertex3f(side_len, side_len, -side_len);	// Top Right Of The Quad (Right)
		glTexCoord2d(1.0f, 0.0f);	glVertex3f(side_len, side_len, side_len);	// Top Left Of The Quad (Right)
		glTexCoord2d(1.0f, 1.0f);	glVertex3f(side_len, -side_len, side_len);	// Bottom Left Of The Quad (Right)
		glTexCoord2d(0.0f, 1.0f);	glVertex3f(side_len, -side_len, -side_len);	// Bottom Right Of The Quad (Right)

		glEnd();

		break;
	case BOTTOM:
		glBindTexture(GL_TEXTURE_2D, textures[face_num]->get_texture());
		glBegin(GL_QUADS);



		glEnd();

		break;
	}
}