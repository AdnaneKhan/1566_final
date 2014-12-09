
#include "Space_Object.hpp"


void Space_Object::updateOrbit() {
	// For Kepler's formula it will be necessary to use the mass of this object, the mass of the parent, and the speed 
	// to calculate parameters for ellispe, etc
	float temp = this->object_orbit.orbital_theta;

	// THERE IS A BIT OF A MATH BUG RIGHT NOW GO OVER IT SO THAT IT ACCELERATES AT THE RIGHT PLACES
	this->object_orbit.orbital_theta = fmod(temp + atanf((2 * orbit_area) / (orbit_rad*orbit_rad))*this->object_orbit.rate_mod, (2 * M_PI));

	if (this->object_orbit.ellipse_a != 0 && this->object_orbit.ellipse_b != 0) {
		float calc_rad = this->object_orbit.curr_rad();
		float x_movement = -calc_rad * cos(this->object_orbit.orbital_theta);
		float y_movement = -calc_rad * sin(this->object_orbit.orbital_theta);

		GLfloat translate_vec[3];

		// TEMPORARY UNTIL Z SHIFTING ALSO CODED
		translate_vec[2] = 0;
		this->object_orbit.focus_translate(translate_vec[0], translate_vec[1]);

		// Move w.r.t parent position
		this->world_pos[0] = this->parent_pos[0] + translate_vec[0] + x_movement;
		this->world_pos[1] = this->parent_pos[1] + translate_vec[1] + y_movement;
		this->world_pos[2] = this->parent_pos[2] + translate_vec[2];

		orbit_rad = sqrt((translate_vec[0] + x_movement)*(translate_vec[0] + x_movement) + (translate_vec[1] + y_movement)*(translate_vec[1] + y_movement));
	}
	else {
		this->world_pos[0] = 0;
		this->world_pos[1] = 0;
		this->world_pos[2] = 0;
	}

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

	glTranslatef(this->parent_pos[0]+t_x, this->parent_pos[1]+t_y, 0);
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
void Space_Object::drawPrep() {
  this->draw_orbit();
  glTranslatef(this->world_pos[0], this->world_pos[1], this->world_pos[2]);

}

void Space_Object::set_orbit(float a, float b, int focus_sel) {
	this->object_orbit.focus_select = focus_sel;
	this->object_orbit.ellipse_a = a;
	this->object_orbit.ellipse_b = b;
	this->orbit_area = (M_PI*a*b)/720;
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

Texture Space_Object::texture_pool[4] = { Texture(EARTHY_TEX, IMG_HEIGHT, IMG_WIDTH), Texture(ICEY_TEX, IMG_HEIGHT, IMG_WIDTH), Texture(BADLAND_TEX, IMG_HEIGHT, IMG_HEIGHT), Texture(MOON_TEX, IMG_HEIGHT, IMG_HEIGHT) };