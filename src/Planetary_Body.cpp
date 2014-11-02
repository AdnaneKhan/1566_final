#ifndef PLANETARY_BODY
#define PLANETARY_BODY
#include "Planetary_Body.hpp"
#endif

#ifndef MATH_HELPER
#include "Math_helper.hpp"
#define MATH_HELPER
#endif


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
	glutSolidSphere(1, 50, 16);
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

	// Object is static
	this->object_orbit.focus_select = 1;
	this->object_orbit.ellipse_a = 0;
	this->object_orbit.ellipse_b = 0;
	this->object_orbit.orbital_theta = 0;
}

Planetary_Body::Planetary_Body() {
	Planetary_Body(random_rot_rate(), random_radius());
	// Delete satellites
	while (this->satellites.size() >= 1) {
		delete(satellites.front());
		satellites.pop_front();
	}
}
