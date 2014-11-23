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
	gluLookAt(position[0], position[1], position[2], position[0] + velocity_dir[0], position[1] + velocity_dir[1], position[2] +velocity_dir[2], orientation[X], orientation[Y], orientation[Z]);

}

void Spaceship::draw() {

}

void Spaceship::update_velocity(speed change) {

	if (this->velocity_mag <= MAX_SPEED && this->velocity_mag >= MIN_SPEED) {
		this->velocity_mag += change;
	}

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

	velocity_dir[X] = -position[X];
	velocity_dir[Y] = -position[Y];
	velocity_dir[Z] = -position[Z];
	normalize_vector(velocity_dir);
	

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

void Spaceship::look_left(float delta_deg) {

	// Rotate the look direction vector around the orientation vector (the up vector
	rot_vector(-delta_deg, orientation[X], orientation[Y], orientation[Z], this->velocity_dir);
#ifdef DEBUG
	std::cout << "Turning the ship left.\n" << velocity_dir[X] << " " << velocity_dir[Y] << " " << velocity_dir[Z] << std::endl;
#endif
}

void Spaceship::look_right(float delta_deg) {
	// Rotate the look direction vector around the orientation vector (the up vector
	rot_vector(+delta_deg, orientation[X], orientation[Y], orientation[Z], this->velocity_dir);
	
#ifdef DEBUG
	std::cout << "Turning the ship right.\n" << velocity_dir[X] << " " << velocity_dir[Y] << " " << velocity_dir[Z] << std::endl;
#endif
}

void Spaceship::update() {
	this->move_forward(this->velocity_mag);
}