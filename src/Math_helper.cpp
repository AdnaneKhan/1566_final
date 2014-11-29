
#include "Math_helper.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

/**
Generates random ellipse
parameters for distance, min 6, max 12
*/
void random_orbit(float &a, float &b) {
	float rand_orbit = (float)(rand() % 800) + 500.0;

	a = rand_orbit *1.1;
	b = rand_orbit *0.9;
}
/**
* Generates a random rotation rate for planet/star
*/
float random_rot_rate() {
	float retV = 0.015f;

	return retV;
}

/*
* Returns a random radius from 1 to 5
*
*/
int random_radius() {
	int retV = (rand() % 20) + 10;

	return retV;
}

/**
* Returns random number of planets from 2-12
*/
int random_planets() {
	return (rand() % 12) + 2;
}

float vector_length(GLfloat vector[3]) {
	return vector_length(vector, 3);
}

float vector_length(GLfloat * vector, int len) {
	float sum = 0;
	for (int i = 0; i < len; i++) {
		sum += vector[i] * vector[i];
	}

	float mag = sqrt(sum);

	return mag;
}

float vector_dot(GLfloat *vec_a, GLfloat *vec_b, int len) {
	float ret_v = 0;

	for (int i = 0; i < len; i++) {
		ret_v += vec_a[i] * vec_b[i];
	}

	return ret_v;
}

float vector_dot(GLfloat vec_a[3], GLfloat vec_b[3]) {
	return vector_dot(vec_a, vec_b, 3);
}

void vector_cross(GLfloat vec_a[3], GLfloat vec_b[3], GLfloat vec_res[3]) {
	vec_res[0] = vec_a[1]*vec_b[2] - vec_a[2]*vec_b[1];
	vec_res[1] = vec_a[2]*vec_b[0] - vec_a[0]*vec_b[2];
	vec_res[2] = vec_a[0]*vec_b[1] - vec_a[1]*vec_b[0];
}
void normalize_vector(GLfloat vector[3] ) {
	float mag = vector_length( (vector) );

	// Divide each component of vector by the magnitude
	for (int i = 0; i < 3; i++) {
		vector[i] /= mag;
	}
}

void normalize_vector(GLfloat * vector, int len) {
	float mag = vector_length(vector, len);

	for (int i = 0; i < len; i++) {
		vector[i] /= mag;
	}
}

float rad_to_deg(float theta_rad) {
	return theta_rad *  (180 / M_PI);
}

float deg_to_rad(float theta_deg) {
	return theta_deg * (M_PI / 180);
}

void rot_vector(GLfloat angle, GLfloat x, GLfloat y, GLfloat z,GLfloat to_rotate[3]) {

	GLfloat denom;
	GLfloat x_norm;
	GLfloat y_norm;
	GLfloat z_norm;

	denom = sqrt(x*x + y*y + z*z);
	// Normalize vector if needed
	if (denom != 1.0f) {
		x_norm = x / denom;
		y_norm = y / denom;
		z_norm = z / denom;

	}
	else {
		x_norm = x;
		y_norm = y;
		z_norm = z;

	}

	// Implementing Rodrigues Rotation Formula from 1566 Slides, it is transposed to opengl column major format
	GLfloat matrix[3][3] = {
		{ cos(angle) + x_norm*x_norm*(1 - cos(angle)), x_norm*y_norm*(1 - cos(angle)) + z_norm*sin(angle), x_norm*z_norm*(1 - cos(angle)) - y_norm*sin(angle) },
		{ x_norm*y_norm*(1 - cos(angle)) - z_norm*sin(angle), cos(angle) + y_norm*y_norm*(1 - cos(angle)), y_norm*z_norm*(1 - cos(angle)) + x_norm*sin(angle) },
		{ z_norm*x_norm*(1 - cos(angle)) + y_norm*sin(angle), z_norm*x_norm*(1 - cos(angle)) - x_norm*sin(angle), z_norm*z_norm*(1 - cos(angle)) + cos(angle) }
	};

	GLfloat tempV[3];

	for (int i = 0; i < 3; i++) {
		tempV[i] = to_rotate[i];
	}

	// Multiply to_rotate by the matrix
	for (int i = 0; i < 3; i++)
	{
		to_rotate[i] = vector_dot(matrix[i], tempV);
	}

	return;
}