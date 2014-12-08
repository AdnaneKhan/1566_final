#include "Raytracer.hpp"

#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328

void Raytrace(float eyeX, float eyeY, float eyeZ, float fieldOfView, float windowW, float windowH) {
	float midpointW, midpointH;
	float t;

	midpointW = windowW / 2;
	midpointH = windowH / 2;

	for (int w = 0; w < windowW; w++) {
		for (int h = 0; h < windowH; h++) {
			Ray cameraRay = Ray(w-midpointW, h-midpointH, midpointW/tan(fieldOfView*.5*(PI/180)));
			cameraRay.SetOrigin(eyeX, eyeY, eyeZ);
			
		}
	}
}

bool HitPlanet(Ray cameraRay, );