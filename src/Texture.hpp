#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include "texgen.hpp"
#include "plandef.hpp"
#include "plandraw.hpp"


#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


typedef int textureType;

class Texture {
public:
	// Load t_x*t_y size texture
	Texture(std::string file_name, int t_x, int t_y);
	Texture(textureType to_generate,int t_x,int t_y);
	

	~Texture();


	textureType get_type();
	// Returns the ID of this texture
	GLuint get_texture();
	std::string debug_name;

	static void blandLandGradient(unsigned char height,
		unsigned char *r, unsigned char *g, unsigned char *b);

	static void iceyGradient(unsigned char height,
		unsigned char *r, unsigned char *g, unsigned char *b);

	static void badLandGradient(unsigned char height,
		unsigned char *r, unsigned char *g, unsigned char *b);


	static void moonyGradient(unsigned char height,
		unsigned char *r, unsigned char *g, unsigned char *b);
private:

	// Loads texture from file,
	void load_texture(std::string file_name, int t_x, int t_y);
	void generate_texture(textureType to_generate);
	
	GLuint texture;
	GLubyte * img;
	GLubyte brownianImage[IMG_HEIGHT][IMG_WIDTH][4];

	textureType texType;

	int x_dim;
	int y_dim;
	int tex;
};

#endif /// END TEXTURE_H GUARD