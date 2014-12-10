#include "Planetary_System.hpp"

Planetary_System::Planetary_System(int sun_radius, int num_planets) {
	this->star = new Planetary_Body(.1, sun_radius,TURB_RED);
	

	this->star->set_orbit(0, 0, 1);
	this->star->set_parent_pos(0, 0, 0);


	// Adds Planets to orbit around the star
	for (int i = 0; i < num_planets; i++) {

		Space_Object * temp = new Planetary_Body(  (.3*(num_planets - i) + .1), random_radius());

		temp->set_parent_pos(0, 0, 0);
		// Set orbit to be origin of system
		Space_Object * temp2 = new Planetary_Body(.3,random_radius()/10);
		temp2->set_orbit(temp->planet_radius*3.0, temp->planet_radius*3.0, 1);
		temp->add_Satelite(temp2);
		star->add_Satelite(temp);
	}

}

std::list<Space_Object *>  Planetary_System::orbiting_planets() {
	return (this->star->satellites);
}

void Planetary_System::update_system() {
	star->updateOrbit();
}

void Planetary_System::draw_system() {
	star->fullDraw();	
}

Planetary_System::Planetary_System() {
	Planetary_System(random_radius(), random_planets());
}

Planetary_System::~Planetary_System() {
	delete(star);
}
