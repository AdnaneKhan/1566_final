#ifndef MATH_HELPER_H
#define MATH_HELPER_H
#define M_PI 3.14159265359

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void random_orbit(float &a, float &b);
/**
* Generates a random rotation rate for planet/star
*/
float random_rot_rate();

/**
*/
int random_radius();

/**
* Returns random number of planets from 2-12
*/
int random_planets();

/*
* @param vector to calculate the lenght of
  @return the length as a float
*/
float vector_length(GLfloat vector[3]);

/**
Calculates cross of vectors
@param vec_a first vector
@param vec_b second vector
@param vec_res will hold resultant cross produt

NOTE Cross product is NOT normalized
*/
void vector_cross(GLfloat vec_a[3], GLfloat vec_b[3], GLfloat vec_res[3]);

float vector_dot(GLfloat vec_a[3], GLfloat vec_b[3]);


void normalize_vector(GLfloat  vector[3] );

float rad_to_deg(float theta_rad);
float deg_to_rad(float theta_deg);

void rot_vector(GLfloat angle, GLfloat x, GLfloat y, GLfloat z, GLfloat to_rotate[3]);

#endif