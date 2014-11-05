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
	glPushMatrix();
	glutSolidSphere(this->planet_radius, 50, 16);
	glPopMatrix();
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
	int pop_c = 0;
	pop_c = drawPrep();
	
	glPushMatrix();

	draw_rotate();
	// Do the actual draw
	draw();
	glPopMatrix();

	
	// Draw satellitess
	if (this->satellites.size() > 0) {
		for (std::list<Space_Object *>::const_iterator iterator = satellites.begin(), end = satellites.end(); iterator != end; ++iterator) {
			(*iterator)->fullDraw();

		}
	}

	// Pop matrixes we pushed during prep stage
	while (pop_c > 0) {
		glPopMatrix();
		pop_c--;
	}
}

Planetary_Body::Planetary_Body(float rotationRate, int radius) {
	this->planet_radius = radius;
	this->rotation_rate = rotationRate;

	// Used to stub the update of orbit
	// before kepler's can be implemented
	this->object_orbit.rate_mod = rotationRate;

	float a;
	float b;
	random_orbit(a, b);
	this->set_orbit(a, b, 1);

	GLfloat temp[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	for (int i = 0; i < 16; i++) {
		rotationMatrix[i] = temp[i];
	}
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