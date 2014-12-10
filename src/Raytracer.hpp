#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "common.h"
#include "Ray.hpp"
#include "Planetary_System.hpp"
#include "Space_Object.hpp"
#include "Planetary_Body.hpp"

class RayTracer {
	public:
	static Planetary_System *curSystem;

	/*** Raytrace ***/
	/*
	Determines which pixes to color on a sphere based upon the algorithms
	found at http://web.cs.wpi.edu/~gogo/courses/cs543/slides/cs543_21_RayTracing_2.pdf
	as well as the slides found at http://people.cs.pitt.edu/~hwa/cs1566. The function
	takes in the viewport and finds which pixels to color based upon the intersection
	between the ray and the sphere through the viewport.
	*/
	static int Raytrace(float x, float y, float z, float cur_planet_pos[3]);

	/*** HitPlanet and GetIntersection ***/
	/*
	Determines whether or not the passed object is intersected by the ray coming from
	the camera and returns the points associated. Shading is done for any planet hit.
	Function is used after HitPlanet(). Returns null if nothing is hit
	*/
	static void SetPlanetarySystem(Planetary_System *system);

	/*
	More generic function that returns a bool based on whether or not there is
	an intersection at all.
	*/
	static bool HitPlanet(Ray ray, Space_Object *sphere);

	static float discriminant(float a, float b, float c);
};



#endif