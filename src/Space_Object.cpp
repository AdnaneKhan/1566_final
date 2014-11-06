
#include "Space_Object.hpp"


void Space_Object::updateOrbit() {
	// Currently stubbed w/ constant angle update
	// For Kepler's formula it will be necessary to use the mass of this object, the mass of the parent, and the speed 
	// to calculate parameters for ellispe, etc
	float temp = this->object_orbit.orbital_theta;
	//this->object_orbit.orbital_theta = fmod((temp + .01*this->object_orbit.rate_mod), (2 * M_PI));

	this->object_orbit.orbital_theta = fmod(temp+atanf((2 * area) / (radius*radius))*this->object_orbit.rate_mod, (2 * M_PI));

	//printf("new theta %f\n", this->object_orbit.orbital_theta);

	// Draw satellitess
	if (this->satellites.size() > 0) {
		for (std::list<Space_Object *>::const_iterator iterator = satellites.begin(), end = satellites.end(); iterator != end; ++iterator) {
			(*iterator)->updateOrbit();

		}
	}
}

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

  // We are now in the plane of orbit that this object is is.
  glPushMatrix();
  push_c++;

  // Translate object to position IN ORBIT
  // Note that we do not do any calculations pertaining to kepler's second
  // law here, those calculations are handled when the orbital theta is updated as kepler's law
  // pertains to the angular speed of an object as a function of its distance from what it is oribiting around
  float radius = this->object_orbit.curr_rad();

  float x_movement = -radius * cos(this->object_orbit.orbital_theta);
  float y_movement = -radius * sin(this->object_orbit.orbital_theta);

  // Translate object such that the orbit's focus is on the origin
  GLfloat translate_vec[2];
  this->object_orbit.focus_translate(translate_vec[0], translate_vec[1]);
  if (this->object_orbit.orbital_theta == this->object_orbit.orbital_theta)
	  glTranslatef(translate_vec[0]+x_movement, translate_vec[1]+y_movement, 0);

  // temp
  float new_rad = sqrt((translate_vec[0] + x_movement)*(translate_vec[0] + x_movement) + (translate_vec[1] + y_movement)*( translate_vec[1] + y_movement));
 // printf("%f new rad\n", new_rad);
  this->radius = new_rad;

  glPushMatrix();
  push_c++;

  GLfloat cross_res[3];
  GLfloat z_vector[3] = { 0.0f, 0.0f, 1.0f };

  // Cross product result now in cross_res
  vector_cross(this->orbit_plane.planeNormal, z_vector, cross_res);
  float vector_len = vector_length(cross_res);
  // This is our rotation axis
  float angle = asinf(vector_len);
  normalize_vector(cross_res);
  //printf("Angle is %f\n", angle);
  // Use axis and angle to transform to new basis.
  //glRotatef(-20, 1, 0,0);
 
  // Object is now in proper position

  return push_c;
}

void Space_Object::set_orbit(float a, float b, int focus_sel) {
	this->object_orbit.focus_select = focus_sel;
	this->object_orbit.ellipse_a = a;
	this->object_orbit.ellipse_b = b;
	this->area = (M_PI*a*b)/720;
	// positive x offset of the focus

	if (a >= b) {
		this->object_orbit.major = 1;
		this->object_orbit.orbit_focus = sqrt(a*a - b*b);
		this->object_orbit.eccentricity = this->object_orbit.orbit_focus / sqrt(this->object_orbit.orbit_focus*this->object_orbit.orbit_focus + b*b);
	}
	else {

		this->object_orbit.major = 2;
		this->object_orbit.orbit_focus = sqrt(b*b - a*a) ;
		this->object_orbit.eccentricity = this->object_orbit.orbit_focus / sqrt(this->object_orbit.orbit_focus*this->object_orbit.orbit_focus + a*a);
	}

	this->orbit_plane.planePoint[0] = 5;
	this->orbit_plane.planePoint[1] = 4;
	this->orbit_plane.planePoint[2] = 0;

	// Get this working
	//this->orbit_plane.planeNormal[0] = 1;
	//this->orbit_plane.planeNormal[1] = 1;
	//this->orbit_plane.planeNormal[2] = 1;
}