
#include "Math_helper.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

/**
* Generates a random rotation rate for planet/star
*/
float random_rot_rate() {
	float retV = 0.015f;

	return retV;
}

/**
*/
int random_radius() {
	float retV = 1;

	return retV;
}

/**
* Returns random number of planets from 2-12
*/
int random_planets() {
	return (rand() % 12) + 2;
}

float vector_length(GLfloat vector[3]) {
	GLfloat sum = vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2];
	GLfloat mag = sqrt(sum);

	return mag;
}

void vector_cross(GLfloat vec_a[3], GLfloat vec_b[3], GLfloat vec_res[3]) {
	vec_res[0] = vec_a[1]*vec_b[2] - vec_a[2]*vec_b[0];
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

float rad_to_deg(float theta_rad) {
	return theta_rad *  (180 / M_PI);
}

float deg_to_rad(float theta_deg) {
	return theta_deg * (M_PI / 180);
}