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
	gluLookAt(position[0], position[1], position[2], velocity_dir[0], velocity_dir[1], velocity_dir[2], 0, 1, 0);


}