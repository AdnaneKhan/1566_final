#include "common.h"

/*** Simple Ray Class ***/
/*
Keeps track of the direction of a ray, along with the unit vector
calculated during intialization. The unit vector has been added such
that we have the normalization of the vector and the initial direction
is still saved, probably for debug. Dir represents the unit vector and
original are the arguments passed.

x, y, z are 0, 1, 2 respectively in the arrays declared publicly.
*/
class Ray {
public:
	float Original[3];
	float Dir[3];
	Ray(float x, float y, float z);
};