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
	drawPlanet(&this->actual_planet, this->planet_tex->get_texture(), this->world_pos, this->planet_radius);
	glPopMatrix();
}

void Planetary_Body::draw_rotate() {
	glRotatef( rad_to_deg(this->rotation),this->rotationAxis[0],this->rotationAxis[1],this->rotationAxis[2]);
}

void Planetary_Body::fullDraw() {
	
	glPushMatrix(); 
	
	drawPrep();
	glPushMatrix();
	//draw_rotate();

	// Do the actual draw
	draw();
	glPopMatrix();
	glPopMatrix();

	// Draw satellitess
	if (this->satellites.size() > 0) {
		for (Space_Object * o : this->satellites) {
			o->fullDraw();	
		}
	}
}

Planetary_Body::Planetary_Body(float rotationRate, int radius, textureType tType) {
	this->planet_radius = radius;
	this->rotation_rate = random_rot_rate();

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

	random_rot_axis(this->rotationAxis);
	this->rotation = 0;
	random_rot_axis(this->orbit_plane.planeNormal);
	this->draw_type = STAR;
	this->planet_tex = &texture_pool[tType];
	createPlanet(&this->actual_planet, this->draw_type, this->planet_radius, .1);
}

Planetary_Body::Planetary_Body(float rotationRate, int radius) {
	textureType  tex_t = (rand() % 4);
	this->planet_radius = radius;
	this->rotation_rate = random_rot_rate();

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

	random_rot_axis(this->rotationAxis);
	random_rot_axis(this->orbit_plane.planeNormal);
	this->rotation = 0;

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

