
#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Drawable.hpp"
#include "Math_helper.hpp"
#include "Texture.hpp"
#include "Ray.hpp"
#include <math.h>
#include <vector>
#include <list>
#include <iostream>

#define GRAV 6.67e-11;

#define PLANET 1
#define COMET 2
#define SPACE_SHIP 3
// POSSIBLE: Creature would have a "squiggly" oribit as a result of
// applying a sin wave fluctuation to the radius resulting from the
// ellipse calculation.
//#define CREATURE 4

class Space_Object : public Drawable {
  public:

	int planet_radius;
	GLfloat world_pos[3];
	std::list<Space_Object *> satellites;
	std::list<Intersection *> toBeShaded;
    int getObjectType();

    /**
    * Handles getting object to its destination according to the simulation
    * and ensuring that it is properly rotated.
    *
    * Draws object relative to its local coordinates
    *
    * Returns to previous frame
    */
	virtual void fullDraw(){};
    /**
    * Performs operations necessary so that the object can be drawn
    * on its local coordinates
    *  - Need to get the plane to correspond to orbital plane
    *  - Need to get object to its current orbital position
    */

	virtual int get_radius(){ return planet_radius; };

    void drawPrep();

	virtual void draw(){};

	int num_satellites();

	/**
	* Updates the orbital position of the object
	* Essentially this is updating the theta
	* while conforming to Kepler's third law of planetary motion
	*/
	void updateOrbit();

    /**
    * Adds satellite to orbit around this object
     */
    void add_Satelite( Space_Object * satellite);
	/**

	Sets the space object to orbit. If there is no specified orbit then this object will be at the same position
	as its parent.

	 @param a
	 @param b
	 @param focus_sel
	*/
	void set_orbit(float a, float b, int focus_sel);

	void set_parent_pos(float x, float y, float z);


	void print_pos();

	void draw_debugs() {
		glPushMatrix();
		glTranslatef(this->world_pos[0], this->world_pos[1], this->world_pos[2]);
		glutSolidTorus(5, 25, 50, 50);
		glPopMatrix();

		for (Space_Object * o : this->satellites) {
			o->draw_debugs();
		}
	}

	/**
	Draws orbit of planet as ellipse
	*/
	void draw_orbit();

  protected:


	  void rotate(float theta_rad);

    typedef struct Orbital_Plane {
		
      GLfloat planeNormal[3];
	  GLfloat planePoint[3];
    } Orbital_Plane;

    // Defines the orbit of space object, note that this ellipse
    // is in polar coordinates
    typedef struct Orbit {

       GLfloat ellipse_a;
       GLfloat ellipse_b;
       GLfloat orbital_theta;
      
	   GLfloat orbit_focus;

	   int major;
	   float eccentricity;
	   float rate_mod;
	   // selects negative or positive focus
	   int focus_select;

	   void focus_translate(GLfloat &x, GLfloat &y) {
		   if (major == 1) {
			   x = orbit_focus;
			   y = 0.0f;

		   }
		   else if (major == 2) {
			   x = 0.0f;
			   y = orbit_focus;

		   }
	   }

		// Returns distance from focus to point on border of sphere given the angle.	  
	   float curr_rad() {
		   if (ellipse_a == 0 || ellipse_b == 0) {
			   return 0;
		   }
		   return ((ellipse_a * ellipse_b) / sqrt((ellipse_b*cos(orbital_theta))*(ellipse_b*cos(orbital_theta)) + (ellipse_a)*(sin(orbital_theta))*(ellipse_a)*(sin(orbital_theta))));
	   }

    } Orbit;

    Space_Object * planet;
    Orbital_Plane orbit_plane;
	Orbit object_orbit;

    // Denotes the type of object
    int object_type;

	float orbit_area;
	float orbit_rad;

	GLfloat parent_pos[3];

	// Pool of textures which planets can use
	static Texture texture_pool[NUM_DYNAMIC_TEXTURES];
	static std::list<Texture> planet_texures;
	static int tex_count;


	GLfloat rotationAxis[3];

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
	float rotation;
};

#endif