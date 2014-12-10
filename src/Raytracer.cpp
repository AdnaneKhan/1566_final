#include "Raytracer.hpp"

#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328


Planetary_System * RayTracer::curSystem = nullptr;

int RayTracer::Raytrace(float x, float y, float z, float cur_planet_pos[3]) {
	std::list<Space_Object *> allSpheres;
	Space_Object *currentPlanet = NULL;
	int flag = 0;

	// Load all planets into big ol list
	for (Space_Object *planet : curSystem->orbiting_planets()) {
		allSpheres.emplace_back(planet);
		for (Space_Object *satellite : planet->satellites) {
			allSpheres.emplace_back(satellite);
		}
	}

	// Make Ray
	Ray cur = Ray(x, y, z);
	cur.SetOrigin(0, 0, 0);

	/*for (Space_Object *planet : allSpheres) {
		if (cur_planet_pos[0] == planet->world_pos[0] && cur_planet_pos[1] == planet->world_pos[1] && cur_planet_pos[2] == planet->world_pos[2]) {
			printf("Match found.\n");
			currentPlanet = planet;
			break;
		}
	}*/

	// Make sure we're on front side of the planet
	//if (!HitPlanet(cur, currentPlanet)) {
		// Determine if Ray intersects with any other planets
		for (Space_Object *planet : allSpheres) {
			if (cur_planet_pos[0] != planet->world_pos[0] || cur_planet_pos[1] != planet->world_pos[1] || cur_planet_pos[2] != planet->world_pos[2]) {
				if (HitPlanet(cur, planet)) {
				
					flag = 1;
					break;
				}
			}
		}
	//}

	return flag;
	
	// For each pixel w
	//for (int w = 0; w < windowW; w++) {

	//	// For each pixel h
	//	for (int h = 0; h < windowH; h++) {

	//		// Determine cameraRay
	//		Ray cameraRay = Ray((w-midpointW)-eyeX, (h-midpointH)-eyeY, (midpointW/tan(fieldOfView*.5*(PI/180)))-eyeZ);
	//		cameraRay.SetOrigin(eyeX, eyeY, eyeZ);

	//		// For each planet
	//		for (Space_Object *planet : allSpheres) {
	//			
	//			// If hit return intersection and generate rays
	//			if (HitPlanet(cameraRay, planet)) {
	//				Intersection *cur = new Intersection(GetIntersection(cameraRay, planet));
	//				Ray lightRay = Ray(cur->point[0], cur->point[1], cur->point[2]);
	//				for (Space_Object *shadowFeeler : allSpheres) {
	//					if (HitPlanet(lightRay, shadowFeeler)) {
	//						planet->toBeShaded.emplace_back(cur);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}

//Intersection GetIntersection(Ray ray, Space_Object *sphere) {
//	float a, b, c;
//	float radius;
//	float cx, cy, cz;
//	float t;
//	Intersection ret(1);
//
//	radius = sphere->get_radius();
//	cx = sphere->world_pos[0];
//	cy = sphere->world_pos[1];
//	cz = sphere->world_pos[2];
//
//	a = ray.Dir[0] * ray.Dir[0] + ray.Dir[1] * ray.Dir[1] + ray.Dir[2] * ray.Dir[2];
//	b = (2 * ray.Dir[0] * (ray.Origin[0] - cx)) + (2 * ray.Dir[1] * (ray.Origin[1] - cy)) + (2 * ray.Dir[2] * (ray.Origin[2] - cz));
//	c = (cx*cx) + (cy*cy) + (cz*cz) + (ray.Origin[0] * ray.Origin[0]) + (ray.Origin[1] * ray.Origin[1]) + (ray.Origin[2] * ray.Origin[2]) +
//		(-2 * (cx*ray.Origin[0] + cy*ray.Origin[1] + cz*ray.Origin[2])) - (radius*radius);
//
//	t = (((-1)*b) - sqrt(discriminant(a, b, c))) / (2 * a);
//
//	for (int i = 0; i < 3; i++) {
//		ret.point[i] = ray.Origin[i] + (t*ray.Dir[i]);
//	}
//
//	return ret;
//}	

bool RayTracer::HitPlanet(Ray ray, Space_Object *sphere) {
	float a, b, c;
	float radius;
	float cx, cy, cz;
	bool ret = false;

	radius = sphere->planet_radius;
	cx = sphere->world_pos[0];
	cy = sphere->world_pos[1];
	cz = sphere->world_pos[2];

	a = ray.Dir[0] * ray.Dir[0] + ray.Dir[1] * ray.Dir[1] + ray.Dir[2] * ray.Dir[2];
	b = (2 * ray.Dir[0] * (ray.Origin[0] - cx)) + (2 * ray.Dir[1] * (ray.Origin[1] - cy)) + (2 * ray.Dir[2] * (ray.Origin[2] - cz));
	c = (cx*cx) + (cy*cy) + (cz*cz) + (ray.Origin[0] * ray.Origin[0]) + (ray.Origin[1] * ray.Origin[1]) + (ray.Origin[2] * ray.Origin[2]) +
		(-2 * (cx*ray.Origin[0] + cy*ray.Origin[1] + cz*ray.Origin[2])) - (radius*radius);

	if (discriminant(a, b, c) >= 0) {
		ret = true;
	}

	return ret;
}


float RayTracer::discriminant(float a, float b, float c) {
	return pow(b, 2) + (-4 * a * c);
}

void RayTracer::SetPlanetarySystem(Planetary_System *system) {
	curSystem = system;
}
