#include "common.h"

/*** Simple Ray Class ***/
/*
Keeps track of the direction of a ray, along with the unit vector
calculated during intialization. The unit vector has been added such
that we have the normalization of the vector and the initial direction
is still saved, probably for debug. Dir represents the unit vector and
original are the arguments passed.

Also contains origin of the ray, in this case will be eyeX, eyeY, and eyeZ.

x, y, z are 0, 1, 2 respectively in the arrays declared publicly.
*/
class Ray {
public:
	float Original[3];
	float Origin[3];
	float Dir[3];
	Ray(float x, float y, float z);
	void Ray::SetOrigin(float x, float y, float z);
};

/*** Intersection Class ***/
/*
Tracks points that need to be modified for shadows, has either one or two points
depending on where the camera ray intersects with the sphere.
*/
class Intersection {
public:
	int numPoints;
	float pointOne[3];
	float pointTwo[3];
	Intersection(int n);
	void Intersection::SetNumPoints(int n);
	void Intersection::SetPointOne(float x, float y, float z);
	void Intersection::SetPointTwo(float x, float y, float z);
};