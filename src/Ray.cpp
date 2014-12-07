#include "Ray.hpp"

Ray::Ray(float x, float y, float z) {
	Dir[0] = x;
	Dir[1] = y;
	Dir[2] = z;

	UnitVector[0] = x / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	UnitVector[1] = y / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	UnitVector[2] = z / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}