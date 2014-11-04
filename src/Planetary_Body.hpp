#ifndef PLANETARY_BODY_H
#define PLANETARY_BODY_H

#include "Space_Object.hpp"
class Planetary_Body: public Space_Object {
  public:
    /**
    * @param x component of vector to rotate about
    * @param y component of vector to rotate about
    * @param z component of vector to rotate about
    * @param theta angle to rotate (in degrees)
    */
      void rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat theta_rad);
      void rotate(GLfloat rotate_vector[3], float theta_rad);
      // TODO find out how textures will play into this.
      Planetary_Body(float rotationRate, int radius);
	  Planetary_Body();
	  ~Planetary_Body();

	  virtual void draw_rotate();
	  virtual void fullDraw();
	  virtual void draw();

  private:
    /**
    * Stores a gl matrix that will be used to rotate this object prior to drawinng  it.
    */
	  GLfloat rotationMatrix[16];
    /**
    * Multiplier in float relative to the cock speed of the universe
    * value from 0 to 1, 1 means it rotates 360 degrees per tick,
    * 0 means it does not rotate
    *
    * This denotes the rotation ABOUT THE OBJECT'S OWN axis.
    */
    float rotation_rate;
	int planet_radius;

};

#endif