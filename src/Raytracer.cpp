#include "Raytracer.hpp"

#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328

void Raytrace(float eyeX, float eyeY, float eyeZ, float fieldOfView, float windowW, float windowH, Planetary_System *system) {
	float midpointW, midpointH;
	float t;
	std::list<Space_Object *> allSpheres;

	t = 0.0;

	midpointW = windowW / 2;
	midpointH = windowH / 2;

	// Load all space objects into one vector
	for (Space_Object *planet : system->planets) {
		allSpheres.emplace_back(planet);
		for (Space_Object *satellite : system->planets) {
			allSpheres.emplace_back(satellite);
		}
	}
	
	// For each pixel w
	for (int w = 0; w < windowW; w++) {

		// For each pixel h
		for (int h = 0; h < windowH; h++) {

			// Determine cameraRay
			Ray cameraRay = Ray(w-midpointW, h-midpointH, midpointW/tan(fieldOfView*.5*(PI/180)));
			cameraRay.SetOrigin(eyeX, eyeY, eyeZ);

			// For each planet
			for (Space_Object *planet : allSpheres) {
				
				// If hit return intersection and generate rays
				if (HitPlanet(cameraRay, planet, &t)) {
					Intersection cur = GetIntersection(cameraRay, planet, &t);
					if (cur.numPoints == 1) {
						Ray lightRay = Ray(cur.pointOne[0], cur.pointOne[1], cur.pointOne[2]);
						// Detemrine if light ray intersects and color pixel
					}
					else if (cur.numPoints == 2) {
						Ray lightRayOne = Ray(cur.pointOne[0], cur.pointOne[1], cur.pointOne[2]);
						Ray lightRayTwo = Ray(cur.pointTwo[0], cur.pointTwo[1], cur.pointTwo[2]);
						// Determine if light ray intersects and color pixel
					}
				}

			}

		}

	}

}

Intersection GetIntersection(Ray ray, Space_Object *sphere, float *t) {
	return NULL;
}

bool HitPlanet(Ray ray, Space_Object *sphere, float *t) {
	return false;
}