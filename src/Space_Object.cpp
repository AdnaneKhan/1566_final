
#include "Space_Object.hpp"


void Space_Object::updateOrbit() {
	// For Kepler's formula it will be necessary to use the mass of this object, the mass of the parent, and the speed 
	// to calculate parameters for ellispe, etc
	float temp = this->object_orbit.orbital_theta;

	// THERE IS A BIT OF A MATH BUG RIGHT NOW GO OVER IT SO THAT IT ACCELERATES AT THE RIGHT PLACES
	this->object_orbit.orbital_theta = fmod(temp + atanf((2 * orbit_area) / (orbit_rad*orbit_rad))*this->object_orbit.rate_mod, (2 * M_PI));

	if (this->object_orbit.ellipse_a != 0 && this->object_orbit.ellipse_b != 0) {
		GLfloat translate_vec[3];
		GLfloat rot_axis[3];

		// Default normal is 0,0,1 (x,y plane)
		GLfloat up_norm[] = { 0, 0, 1 };

		float calc_rad = this->object_orbit.curr_rad();
		float x_movement = -calc_rad * cos(this->object_orbit.orbital_theta);
		float y_movement = -calc_rad * sin(this->object_orbit.orbital_theta);

		// W.r.t parent there is no vertical translation at this stage (it is calculcated during rotation phase)
		translate_vec[2] = 0;
		this->object_orbit.focus_translate(translate_vec[0], translate_vec[1]);

		// Calculate rotation such that point will lie on new plane defined by orbital normal and the point of the parent.
		GLfloat trans_norm[3];
		GLfloat trans_non_normalizes[3];
		
		// Position w.r.t parent
		trans_non_normalizes[0] = trans_norm[0] = x_movement + translate_vec[0];
		trans_non_normalizes[1] = trans_norm[1] = y_movement + translate_vec[1];
		trans_non_normalizes[2] = trans_norm[2] = 0.0f;

		// Normalize vector (used for plane calculations)s
		normalize_vector(trans_norm);

		/**
		* CITING:
		* https://gamedev.stackexchange.com/questions/50880/rotating-plane-to-be-parallel-to-given-normal-via-change-of-basis
		* for mathematical reference to this calculation
		*/

		vector_cross(up_norm, this->orbit_plane.planeNormal, rot_axis);
		normalize_vector(rot_axis);

		// Calculate rotation angle to switch to new plane
		GLfloat rot_angle = asin(vector_length(rot_axis));

		// Rotate the point to lie on new plane
		rot_vector((rot_angle), rot_axis[0], rot_axis[1], rot_axis[2], trans_non_normalizes);
		
		// Move w.r.t parent position
		this->world_pos[0] = this->parent_pos[0] + trans_non_normalizes[0];
		this->world_pos[1] = this->parent_pos[1] + trans_non_normalizes[1]; 
		this->world_pos[2] = this->parent_pos[2] + trans_non_normalizes[2];

		// Calculate new orbital radius (used for kepler's calculations)
		orbit_rad = sqrt((translate_vec[0] + x_movement)*(translate_vec[0] + x_movement) + (translate_vec[1] + y_movement)*(translate_vec[1] + y_movement));
	}
	else {
		this->world_pos[0] = 0;
		this->world_pos[1] = 0;
		this->world_pos[2] = 0;
	}

	rotate(this->rotation_rate);

	// Update Satellites
	if (this->satellites.size() > 0) {
		for (Space_Object * o : this->satellites) {
			o->set_parent_pos(this->world_pos[0], this->world_pos[1], this->world_pos[2]);
			o->updateOrbit();
		}
	}
}


void Space_Object::rotate( float angle_rad) {
	this->rotation = fmod(rotation + angle_rad, 2 * M_PI);
}

void Space_Object::draw_orbit() {
	
	glPushMatrix();

	float t_x;
	float t_y;

	this->object_orbit.focus_translate(t_x, t_y);;

	glColor3f(0, 1, 0);
	glBegin(GL_LINE_LOOP);

	int i;
	for (i = 0; i<360; i++)
	{
		float rad = deg_to_rad(i);
		// Calculate rotation such that point will lie on new plane defined by orbital normal and the point of the parent.
		GLfloat trans_norm[3];
		GLfloat trans_non_normalizes[3];


		trans_non_normalizes[0] = trans_norm[0] =cos(rad)*this->object_orbit.ellipse_a + t_x;
		trans_non_normalizes[1] = trans_norm[1] = sin(rad)*this->object_orbit.ellipse_b + t_y;
		trans_non_normalizes[2] = trans_norm[2] =  0.0f;
		normalize_vector(trans_norm);

		GLfloat up_norm[] = { 0, 0, 1 };
		GLfloat rot_axis[3];
		vector_cross(up_norm, this->orbit_plane.planeNormal, rot_axis);
		normalize_vector(rot_axis);

		GLfloat rot_angle = asin(vector_length(rot_axis));
		rot_vector((rot_angle), rot_axis[0], rot_axis[1], rot_axis[2], trans_non_normalizes);

		trans_non_normalizes[0] += this->parent_pos[0];
		trans_non_normalizes[1] += this->parent_pos[1];
		trans_non_normalizes[2] += this->parent_pos[2];
		glVertex3fv(trans_non_normalizes);
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

	random_rot_axis(this->orbit_plane.planeNormal);
	normalize_vector(this->orbit_plane.planeNormal);
}

void Space_Object::set_parent_pos(float x, float y, float z) {
	this->parent_pos[0] = x;
	this->parent_pos[1] = y;
	this->parent_pos[2] = z;

	this->orbit_plane.planePoint[0] = x;
	this->orbit_plane.planePoint[1] = y;
	this->orbit_plane.planePoint[2] = z;

}

void Space_Object::print_pos() {
	std::cout << "X: " << this->world_pos[0] << "Y: " << this->world_pos[1] << "Z: " << this->world_pos[2] << std::endl;
}

Texture Space_Object::texture_pool[NUM_DYNAMIC_TEXTURES] = { Texture(EARTHY_TEX, IMG_HEIGHT, IMG_WIDTH), Texture(ICEY_TEX, IMG_HEIGHT, IMG_WIDTH), Texture(BADLAND_TEX, IMG_HEIGHT, IMG_HEIGHT), Texture(MOON_TEX, IMG_HEIGHT, IMG_HEIGHT) ,Texture(TURB_RED, IMG_HEIGHT,IMG_WIDTH)};