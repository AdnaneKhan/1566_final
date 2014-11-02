#ifndef PLANETARY_SYSTEM
#define PLANETARY_SYSTEM
#include "Planetary_System.hpp"
#endif
#ifndef PLANETARY_BODY
#define PLANETARY_BODY
#include "Planetary_Body.hpp"
#endif

Planetary_System::Planetary_System(int sun_radius, int num_planets) {
	this->star = new Planetary_Body(sun_radius, num_planets);
	// Adds Planets to orbit around the star
	for (int i = 0; i < num_planets; i++) {
		Space_Object * temp = new Planetary_Body();
		// Set orbit to be origin of system
		temp->set_orbit(0,0,1);
		star->add_Satelite(temp);
	}

}

Planetary_System::Planetary_System() {
	Planetary_System(random_radius(), random_planets());
}

Planetary_System::~Planetary_System() {
	delete(star);
}
