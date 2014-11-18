#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <fstream>
#include <iostream>
#include <array>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Texture {
public:
	// Load 256^2 texture
	Texture(std::string file_name, int t_x, int t_y);
	~Texture();

	// Returns the name of this texture
	GLuint get_texture();
	std::string debug_name;
private:

	// Loads texture from file,
	void load_texture(std::string file_name, int t_x, int t_y);
	
	GLuint texture;
	GLubyte * img;

	int x_dim;
	int y_dim;
	int tex;
};

#endif /// END TEXTURE_H GUARD