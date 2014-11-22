#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Drawable.hpp"
#include "Math_helper.hpp"

#define MOVEMENT_TIME 20
#define X 0
#define Y 1
#define Z 2


#define MIN_SPEED 0
#define MAX_SPEED 200

class Spaceship : public Drawable {

public:
	
	Spaceship();

	/**
	Draws the spaceship in correct orientation

	*/
	void draw();



	// Control interface of the shi

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

	/**
	Advances the ship forward in its velocity direction
	*/
	void move_forward(float delta_mag);
	void move_backward(float delta_mag);


	/*
	
	To rotate left we rotate around the up vector as our axis
	
	*/
	void look_left(float delta_deg);

	/*
	To rotate left we rotate around the up vector as our axis
	*/
	void look_right(float delta_deg);


	/*
	
	In this case we rotate around the axis that results from the cross product of the up vector and the velocity_dir vector
	This is because the velocity dir and orientation vectors are orthogonal.
	
	note that we are rotating the look direction and orientation vectors

	*/
	void look_up(float delta_deg);

	/*

	In this case we rotate around the axis that results from the cross product of the up vector and the velocity_dir vector
	This is because the velocity dir and orientation vectors are orthogonal.

	note that we are rotating the look direction and orientation vectors

	*/
	void look_down(float delta_deg);

	// Rotation matrix representing rotation of ship
	GLfloat rotation[16];


	static GLfloat velocity_dir[3];
	static GLfloat velocity_mag;

	// Position of ship in world coordinates
	static GLfloat position[3];

	/*
	This is essentially the up vector of the ship
	*/
	static GLfloat orientation[3];

	
};


#endif // END SPACESHIP_H GUARD