#include "Planetary_System.hpp"

Planetary_System::Planetary_System(int sun_radius, int num_planets) {
	this->star = new Planetary_Body(.1, sun_radius);
	this->star->set_orbit(0, 0, 1);
	this->star->set_parent_pos(0, 0, 0);
	// Adds Planets to orbit around the star
	for (int i = 0; i < num_planets; i++) {

		Space_Object * temp = new Planetary_Body((.3*(i) + .1), random_radius());
		temp->set_parent_pos(0, 0, 0);
		// Set orbit to be origin of system
		Space_Object * temp2 = new Planetary_Body(.3,random_radius()/10);
		temp2->set_orbit(27.2, 27.0, 1);
		temp->add_Satelite(temp2);
		star->add_Satelite(temp);
	}
}

void Planetary_System::update_system() {
	star->updateOrbit();
}
void Planetary_System::draw_system() {
	//star->draw_debugs();
	star->fullDraw();
	
}

Planetary_System::Planetary_System() {
	Planetary_System(random_radius(), random_planets());
}

Planetary_System::~Planetary_System() {
	delete(star);
}
