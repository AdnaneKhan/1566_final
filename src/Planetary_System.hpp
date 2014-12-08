#ifndef PLANETARY_SYSTEM
#define PLANETARY_SYSTEM

#include <vector>
#include "Space_Object.hpp"
#include "Planetary_Body.hpp"
#include "Math_helper.hpp"

#include <list>

class Planetary_System {
  public:

	void update_system();
    Planetary_System(int sun_radius, int num_planets);
	Planetary_System();
    ~Planetary_System();
	void draw_system();


	// Vector holding planets orbiting the center sun
	std::vector<Space_Object *> planets;


  private:
	
	  // Star of this system
	  Space_Object * star;
	 

};
#endif