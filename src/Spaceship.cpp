#include "Spaceship.hpp"


void Spaceship::stop_ship() {
	this->velocity_mag = 0.0f;
}

void Spaceship::get_position(GLfloat to_set[3]) {

	for (int i = 0; i << 3; i++) {
		to_set[i] = this->position[i];
	}

}

void Spaceship::set_camera() {

	// Spaceship camera now correctly positioned
	gluLookAt(position[0], position[1], position[2], velocity_dir[0], velocity_dir[1], velocity_dir[2], orientation[X], orientation[Y], orientation[Z]);


}

void Spaceship::draw() {

}

void Spaceship::move_forward(float delta_mag) {
	for (int i = 0; i < 3; i++) {
		position[i] += velocity_dir[i]*(delta_mag);
	}
}

void Spaceship::move_backward(float delta_mag) {
	for (int i = 0; i < 3; i++) {
		position[i] -= velocity_dir[i] * (delta_mag);
	}
}

/**
Set initial position of spaceship
*/
Spaceship::Spaceship() {

	position[X] = -1000.0;
	position[Y] = -1000.0;
	position[Z] = 300.0;

	velocity_dir[X] = 0.0;
	velocity_dir[Y] = 0.0;
	velocity_dir[Z] = 0.0;

	orientation[X] = 0.0;
	orientation[Y] = 0.00;
	orientation[Z] = 1.0;

}


void Spaceship::look_up(float delta_deg) {
	GLfloat rotate_around[3];

	vector_cross(this->orientation, this->velocity_dir, rotate_around);

	rot_vector(-delta_deg, rotate_around[X], rotate_around[Y], rotate_around[Z], this->velocity_dir);
	rot_vector(-delta_deg, rotate_around[X], rotate_around[Y], rotate_around[Z], this->orientation);


}

void Spaceship::look_down(float delta_deg) {
	GLfloat rotate_around[3];

	vector_cross(this->orientation, this->velocity_dir, rotate_around);

	rot_vector(-delta_deg, rotate_around[X], rotate_around[Y], rotate_around[Z], this->velocity_dir);
	rot_vector(-delta_deg, rotate_around[X], rotate_around[Y], rotate_around[Z], this->orientation);


}

