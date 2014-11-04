
#include "Space_Object.hpp"
void Space_Object::updateOrbit() {
	// Currently stubbed, add in keplers later
	float temp = this->object_orbit.orbital_theta;
	this->object_orbit.orbital_theta = fmod((temp + .05*this->object_orbit.rate_mod), (2 * M_PI));

	// Draw satellitess
	if (this->satellites.size() > 0) {
		for (std::list<Space_Object *>::const_iterator iterator = satellites.begin(), end = satellites.end(); iterator != end; ++iterator) {
			(*iterator)->updateOrbit();

		}
	}
}

// TODO
//
 void Space_Object::add_Satelite(Space_Object * satellite) {
	 // Add satellite to orbit around
	 satellites.emplace_back(satellite);

}

 int Space_Object::num_satellites()
 {
	 return satellites.size();
 }
/**
* CITING:
* https://gamedev.stackexchange.com/questions/50880/rotating-plane-to-be-parallel-to-given-normal-via-change-of-basis
* for mathematical reference to this calculation
*/
int Space_Object::drawPrep() {
 
  int push_c = 0;
  GLfloat cross_res[3];
  GLfloat z_vector[3] = {0.0f,0.0f,1.0f};

  // Cross product result now in cross_res
  vector_cross(this->orbit_plane.planeNormal,z_vector, cross_res);
  float vector_len = vector_length(cross_res);
  // This is our rotation axis
  normalize_vector(cross_res);
  float angle = asinf(vector_len);
  // Use axis and angle to transform to new basis.
  glRotatef(angle, cross_res[0], cross_res[1], cross_res[2]);
 
  // We are now in the plane of orbit that this object is is.
  glPushMatrix();
  push_c++;

  // Translate object to position IN ORBIT
  // Note that we do not do any calculations pertaining to kepler's second
  // law here, those calculations are handled when the orbital theta is updated as kepler's law
  // pertains to the angular speed of an object as a function of its distance from what it is oribiting around
  float radius = this->object_orbit.curr_rad();

  float x_movement = radius * cos(this->object_orbit.orbital_theta);
  float y_movement = radius * sin(this->object_orbit.orbital_theta);
  glTranslatef(x_movement, y_movement, 0);

  // Translate object such that the orbit's focus is on the origin
  glTranslatef(this->object_orbit.orbit_focus_x, 0, 0);

  glPushMatrix();
  push_c++;

  // Object is now in proper position

  return push_c;
}

void Space_Object::set_orbit(float a, float b, int focus_sel) {
	this->object_orbit.focus_select = focus_sel;
	this->object_orbit.ellipse_a = a;
	this->object_orbit.ellipse_b = b;
	// positive x offset of the focus
	this->object_orbit.orbit_focus_x = sqrt(a*a - b*b) / 2;

}