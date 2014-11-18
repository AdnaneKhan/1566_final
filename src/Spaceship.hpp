#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Drawable.hpp"
#include "Math_helper.hpp"

#define MOVEMENT_TIME 20

class Spaceship : public Drawable {

public:
	
	Spaceship();

	/**
	Draws the spaceship in correct orientation

	*/
	void draw();


	/*
	Positions the camera to be aligned with the spaceship.
	*/
	void set_camera();


	void get_position(GLfloat to_set[3]);

	void get_lookdir(GLfloat to_set[3]);

	/*
	Changes the velocity by the delta
	*/
	void update_velocity(float delta);

	/*
	Stops the ship (sets magnitude of veclocity to 0)
	*/
	void stop_ship();
private:

	/**
	 Function calls itself on 
	*/
	void movement();


	void set_velocity(float new_vel);


	// Rotation matrix representing rotation of ship
	GLfloat rotation[16];


	GLfloat velocity_dir[3];
	GLfloat velocity_mag;

	// Position of ship in world coordinates
	GLfloat position[3];

	
};


#endif // END SPACESHIP_H GUARD