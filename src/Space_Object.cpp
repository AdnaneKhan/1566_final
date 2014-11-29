
#include "Space_Object.hpp"


void Space_Object::updateOrbit() {
	// For Kepler's formula it will be necessary to use the mass of this object, the mass of the parent, and the speed 
	// to calculate parameters for ellispe, etc
	float temp = this->object_orbit.orbital_theta;

	this->object_orbit.orbital_theta = fmod(temp+atanf((2 * area) / (radius*radius))*this->object_orbit.rate_mod, (2 * M_PI));

	//////////////////////////////// CURRENTLY BORROWING CODE FROM DRAW PREP
	if (this->object_orbit.ellipse_a != 0 && this->object_orbit.ellipse_b != 0) {
		float calc_rad = this->object_orbit.curr_rad();
		float x_movement = -calc_rad * cos(this->object_orbit.orbital_theta);
		float y_movement = -calc_rad * sin(this->object_orbit.orbital_theta);

		GLfloat translate_vec[2];
		this->object_orbit.focus_translate(translate_vec[0], translate_vec[1]);

		// Set position of parent
		this->world_pos[0] = this->parent_pos[0] + translate_vec[0] + x_movement;
		this->world_pos[1] = this->parent_pos[1] + translate_vec[1] + y_movement;
	}
	else {
		this->world_pos[0] = 0;
		this->world_pos[1] = 0;
		this->world_pos[2] = 0;
	}

	/// END BORROWED CODE
	////////////////////////////////////////////////////////////////////////////

	// Update Satellites
	if (this->satellites.size() > 0) {
		for (Space_Object * o : this->satellites) {
			o->set_parent_pos(this->world_pos[0], this->world_pos[1], this->world_pos[2]);
			o->updateOrbit();
		}
	}
}

void Space_Object::draw_orbit() {
	
	glPushMatrix();

	float t_x;
	float t_y;

	this->object_orbit.focus_translate(t_x, t_y);;

	glTranslatef(t_x, t_y, 0);
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_LOOP);

	int i;
	for (i = 0; i<360; i++)
	{
		float rad = deg_to_rad(i);
		glVertex2f(cos(rad)*this->object_orbit.ellipse_a,
		sin(rad)*this->object_orbit.ellipse_b);
	}

	glEnd();

	glPopMatrix();
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
	this->draw_orbit();

  int push_c = 0;

  // We are now in the plane of orbit that this object is is.
  glPushMatrix();
  push_c++;

  // Translate object to position IN ORBIT
  // Note that we do not do any calculations pertaining to kepler's second
  // law here, those calculations are handled when the orbital theta is updated as kepler's law
  // pertains to the angular speed of an object as a function of its distance from what it is oribiting around
  float calc_radius = this->object_orbit.curr_rad();

  float x_movement = -calc_radius * cos(this->object_orbit.orbital_theta);
  float y_movement = -calc_radius * sin(this->object_orbit.orbital_theta);

  // Translate object such that the orbit's focus is on the origin
  GLfloat translate_vec[2];
  this->object_orbit.focus_translate(translate_vec[0], translate_vec[1]);


  if (this->object_orbit.orbital_theta == this->object_orbit.orbital_theta)
	  glTranslatef(translate_vec[0]+x_movement, translate_vec[1]+y_movement, 0);


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
 //glRotatef(20, cross_res[0], cross_res[1],cross_res[2]);
 
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

	// TODO: generate random norma to devaite from current
	this->orbit_plane.planeNormal[0] = 1;
	this->orbit_plane.planeNormal[1] = 1;
	this->orbit_plane.planeNormal[2] = 1;
}

void Space_Object::set_parent_pos(float x, float y, float z) {
	this->parent_pos[0] = x;
	this->parent_pos[1] = y;
	this->parent_pos[2] = z;
}

void Space_Object::print_pos() {
	std::cout << "X: " << this->world_pos[0] << "Y: " << this->world_pos[1] << "Z: " << this->world_pos[2] << std::endl;
}