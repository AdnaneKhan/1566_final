#ifndef PLANETARY_BODY_H
#define PLANETARY_BODY_H

#include "Space_Object.hpp"
#include "Texture.hpp"
#include "plangen.hpp"

/**
* This class will hold state concerning a planetary object
*  
* - Rotation about its own axis
* - Texture Properties
* - Shape properties (if not a sphere, etc)
*/
class Planetary_Body: public Space_Object {
  public:


      Planetary_Body(float rotationRate, int radius);
	  Planetary_Body(float rotationRate, int radius, textureType tType);
	  Planetary_Body();
	  ~Planetary_Body();

	  // Inherited functions from Space_object
	  virtual void draw_rotate();
	  virtual void fullDraw();
	  virtual void draw();

  private:

	 Planet actual_planet;
	 PTypeEnum draw_type;

	Texture * planet_tex;
};

#endif