#ifndef PLANETARY_BODY
#include "Planetary_Body.hpp"
#define PLANETARY_BODY
#endif

#include <vector>

#define PLANET 1
#define COMET 2
#define SPACE_SHIP 3
// POSSIBLE: Creature would have a "squiggly" oribit as a result of
// applying a sin wave fluctuation to the radius resulting from the
// ellipse calculation.
//#define CREATURE 4

class SpaceObject {
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
    virtual void fullDraw();
    /**
    * Performs operations necessary so that the object can be drawn
    * on its local coordinates
    *  - Need to get the plane to correspond to orbital plane
    *  - Need to get object to its current orbital position
    *  - Need to rotate the object about its own axes
    */
    virtual void drawPrep();

    /**
    * Adds satellite to orbit around this object
     */
    void add_Satelite( SpaceObject * satellite);


    SpaceObject();

    ~SpaceObject();

  protected:
    std::vector<SpaceObject *> satellites;

    typedef struct OrbitalPlane {
      float planeNormal[3];
      float planePoint;
    } OrbitalPlane;

    // Defines the orbit of space object, note that this ellipse
    // is in polar coordinates
    typedef struct Orbit {
      // Referring to https://math.stackexchange.com/questions/315386/ellipse-in-polar-coordinates
      // for mathematical ref about polar formula of ellipse.
      float ellipse_a;
      float ellipse_b;
      float orbital_theta;
      // Focus of the ellipse which the object is orbiting around
      float orbit_focus;
      OrbitalPlane plane;
    } Orbit;

    /**
    * Updates the orbital position of the object
    * Essentially this is updating the theta
    * while conforming to Kepler's third law of planetary motion
    */
    void updateOrbit();


    Planetary_Body planet;

  private:


    int current_x;
    int current_y;
    int current_z;
    // Denotes the type of object
    int object_type;
    // Angle in radians of position about its orbit

};
