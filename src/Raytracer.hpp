#include "common.h"
#include "Ray.hpp"

/*** Raytrace ***/
/* 
Determines which pixes to color on a sphere based upon the algorithms 
found at http://web.cs.wpi.edu/~gogo/courses/cs543/slides/cs543_21_RayTracing_2.pdf
as well as the slides found at http://people.cs.pitt.edu/~hwa/cs1566. The function
takes in the viewport and finds which pixels to color based upon the intersection
between the ray and the sphere through the viewport.
*/
void Raytrace(float eyeX, float eyeY, float eyeZ, float windowW, float windowH);

/*** HitPlanet ***/
/*
Determines whether or not the passed object is intersected by the ray coming from
the camera. Shading is done for any planet hit.
*/
bool HitPlanet(Ray cameraRay);