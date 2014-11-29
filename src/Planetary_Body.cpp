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

	glColor3b(0, 0, 1);
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
	
	
	glPushMatrix();
	pop_c = drawPrep();
	// Do the actual draw
	draw();
	draw_rotate();
	glPopMatrix();

	
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