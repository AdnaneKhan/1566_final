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