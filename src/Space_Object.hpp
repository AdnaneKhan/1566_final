
#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Drawable.hpp"
#include "Math_helper.hpp"

#include <math.h>
#include <vector>
#include <list>
#include <iostream>

#define PLANET 1
#define COMET 2
#define SPACE_SHIP 3
// POSSIBLE: Creature would have a "squiggly" oribit as a result of
// applying a sin wave fluctuation to the radius resulting from the
// ellipse calculation.
//#define CREATURE 4

class Space_Object : public Drawable {
  public:

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

    int drawPrep();

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

  protected:

    typedef struct Orbital_Plane {
      GLfloat planeNormal[3];
      GLfloat planePoint;
    } Orbital_Plane;

    // Defines the orbit of space object, note that this ellipse
    // is in polar coordinates
    typedef struct Orbit {
      // Referring to https://math.stackexchange.com/questions/315386/ellipse-in-polar-coordinates
      // for mathematical ref about polar formula of ellipse.
       GLfloat ellipse_a;
       GLfloat ellipse_b;
       GLfloat orbital_theta;
      
	   GLfloat orbit_focus_x;
	   float rate_mod;
	   // selects negative or positive focus
	   int focus_select;
	   // Returns the distance from the center of the ellipse of the object
	   float curr_rad() {
		 return ((ellipse_a * ellipse_b) / sqrt((ellipse_b*cos(orbital_theta))*(ellipse_b*cos(orbital_theta)) + (ellipse_a)*(sin(orbital_theta))*(ellipse_a)*(sin(orbital_theta))));
	   }
	   // returns distance from the selected focus
	   float actual_dist() {

	   }

      Orbital_Plane plane;
    } Orbit;


	  std::list<Space_Object *> satellites;
    Space_Object * planet;
    Orbital_Plane orbit_plane;
	Orbit object_orbit;
    int current_x;
    int current_y;
    int current_z;
    // Denotes the type of object
    int object_type;
    // Angle in radians of position about its orbit

};

#endif