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

void Ray::SetFlag(int n) {
	flag = n;
}


Vertex::Vertex(int n) {
	numPoints = n;
}

void Vertex::SetPoint(float x, float y, float z) {
	point[0] = x;
	point[1] = y;
	point[2] = z;
}

Point::Point(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}