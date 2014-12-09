#include "Ray.hpp"

Ray::Ray(float x, float y, float z) {
	Original[0] = x;
	Original[1] = y;
	Original[2] = z;

	Dir[0] = x / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	Dir[1] = y / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	Dir[2] = z / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Ray::SetOrigin(float x, float y, float z) {
	Origin[0] = x;
	Origin[1] = y;
	Origin[2] = z;
}

Intersection::Intersection(int n) {
	numPoints = n;
}

void Intersection::SetNumPoints(int n) {
	numPoints = n;
}

void Intersection::SetPointOne(float x, float y, float z) {
	pointOne[0] = x;
	pointOne[1] = y;
	pointOne[2] = z;
}

void Intersection::SetPointTwo(float x, float y, float z) {
	pointTwo[0] = x;
	pointTwo[1] = y;
	pointTwo[2] = z;
}