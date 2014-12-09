#include "Planetary_Body.hpp"
#include "Math_helper.hpp"


#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
/**
* CURRENTLY STUBBED using just a radius 1 sphere
*/
void Planetary_Body::draw() {
	drawPlanet(&this->actual_planet, this->planet_tex->get_texture());
}

void Planetary_Body::rotate(GLfloat rot_axis[3], float angle_rad) {
	rotate(rot_axis[0], rot_axis[1], rot_axis[2], angle_rad);
}

void Planetary_Body::rotate(GLfloat x, GLfloat y, GLfloat z, float angle_rad) {
	glPushMatrix();
	glMultMatrixf(rotationMatrix);
	glRotatef(rad_to_deg(angle_rad), x, y,z);
	glGetFloatv(GL_MODELVIEW_MATRIX, rotationMatrix);
	glPopMatrix();
}

void Planetary_Body::draw_rotate() {
	glMultMatrixf(rotationMatrix);
}

void Planetary_Body::fullDraw() {

	drawPrep();
	// Do the actual draw
	draw();
	draw_rotate();
	
	// Draw satellitess
	if (this->satellites.size() > 0) {
		for (Space_Object * o : this->satellites) {
			
			o->fullDraw();
		
		}
	}
}

Planetary_Body::Planetary_Body(float rotationRate, int radius) {
	this->planet_radius = radius;
	this->rotation_rate = rotationRate;

	// Setting values pertaining to the planet's orbit around its parent body
	this->object_orbit.rate_mod = rotationRate;

	float a;
	float b;
	random_orbit(a, b);

	this->set_orbit(a, b, 1);

	// Setting rotation matrix for rotation about its own axis
	GLfloat temp[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	for (int i = 0; i < 16; i++) {
		rotationMatrix[i] = temp[i];
	}


	this->draw_type = TEXTURED;
	this->planet_tex = &texture_pool[(rand() % 4)];
	createPlanet(&this->actual_planet, this->draw_type, this->planet_radius, .1);


}

Planetary_Body::Planetary_Body() {
	Planetary_Body(random_rot_rate(), random_radius());
}

Planetary_Body::~Planetary_Body() {
	// Delete satellites
	while (this->satellites.size() >= 1) {
		delete(satellites.front());
		satellites.pop_front();
	}
}

