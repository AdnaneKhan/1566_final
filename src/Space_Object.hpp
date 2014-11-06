
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
		  // float radius = ((ellipse_a * ellipse_b) / sqrt((ellipse_b*cos(orbital_theta))*(ellipse_b*cos(orbital_theta)) + (ellipse_a)*(sin(orbital_theta))*(ellipse_a)*(sin(orbital_theta))));
		  // float x_movement;
		  // float y_movement;
		  // focus_translate(x_movement, y_movement);
		  // x_movement += radius * cos(orbital_theta);
		  // y_movement += radius * sin(orbital_theta);

		  // return sqrt(x_movement*x_movement + y_movement*y_movement);
		  //// return ellipse_a*(1 - eccentricity*eccentricity) / (1 + cos(orbital_theta));
	   }

	 
      Orbital_Plane plane;
    } Orbit;

	std::list<Space_Object *> satellites;
    Space_Object * planet;
    Orbital_Plane orbit_plane;
	Orbit object_orbit;


    // Denotes the type of object
    int object_type;
   
	// Mass to be used for kepler's calculations
	double mass;
	// to be ignored if object is stationary
	double parentmass;

//
	float radius;
	float area;
};

#endif