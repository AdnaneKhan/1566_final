#ifndef PLANETARY_SYSTEM
#define PLANETARY_SYSTEM

#include <vector>
#include "Space_Object.hpp"
#include "Planetary_Body.hpp"
#include "Math_helper.hpp"
#include <deque>
#include <list>

class Planetary_System {
  public:

	/*
	  Draws the planetary system which includes the star and all planets orbiting it.

	*/
	void draw_system();

	/*
		Updates all positions of planets based on one time step.
	*/
	void update_system();


	/*
	 Initializes a planetary system with a sun with given radius and set number of planets
	*/
    Planetary_System(int sun_radius, int num_planets);

	/*
	Initializes a random planetary system with
	*/
	Planetary_System();


    ~Planetary_System();

	std::deque<Space_Object *>  orbiting_planets();

  private:
	
	  // Star of this system
	  Space_Object * star;
	 

};
#endif