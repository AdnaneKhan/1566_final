#ifndef SPACEBOX_H
#define SPACEBOX_H

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Texture.hpp"

#define TOP 0
#define FRONT 1
#define BACK 2
#define LEFT 3
#define RIGHT 4
#define BOTTOM 5


/**
Defines a spacebox (essentially a skybox) for the solar system

*/
class Spacebox {	
public:
	/*
		Creates a skybox with side length size, and textured with the 6 side textures passed in
	*/
	Spacebox(int size, Texture * side1);
	~Spacebox();

	// Draws skybox at the specified position
	void draw_skybox();

private:

	int side_len;
	Texture * textures[6];
	
	 void apply_textures();
	 void draw_face();
	
	 GLfloat mat_amb_diff[4];
	 GLfloat mat_specular[4];
	 GLfloat mat_low_shininess[1];
	 GLfloat mat_emission[4];

};

#endif