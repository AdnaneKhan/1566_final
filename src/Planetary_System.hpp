
#include <vector>

#ifndef SPACE_OBJECT
#define SPACE_OBJECT
#include "Space_Object.hpp"
#endif

#ifndef PLANETARY_BODY
#define PLANETARY_BODY
#include "Planetary_Body.hpp"
#endif

#ifndef MATH_HELPER
#define MATH_HELPER
#include "Math_helper.hpp"
#endif

class Planetary_System {
  public:

	void update_system();
    Planetary_System(int sun_radius, int num_planets);
	Planetary_System();
    ~Planetary_System();
  private:
	// Vector holding planets orbiting the center sun
	  std::vector<Space_Object *> planets;
	  // Star of this system
	  Space_Object * star;
};
