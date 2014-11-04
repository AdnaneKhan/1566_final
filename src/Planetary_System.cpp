#include "Planetary_System.hpp"

Planetary_System::Planetary_System(int sun_radius, int num_planets) {
	this->star = new Planetary_Body(0, sun_radius);
	// Adds Planets to orbit around the star
	for (int i = 0; i < num_planets; i++) {
		Space_Object * temp = new Planetary_Body((num_planets+1-(i+1))*.60,1);
		// Set orbit to be origin of system
		star->add_Satelite(temp);
	}
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
