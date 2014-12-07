#include "common.h"
#include "Ray.hpp"

/*** Raytrace ***/
/* 
Determines which pixes to color on a sphere based upon the algorithms 
found at http://web.cs.wpi.edu/~gogo/courses/cs543/slides/cs543_21_RayTracing_2.pdf
as well as the slides found at http://people.cs.pitt.edu/~hwa/cs1566. The function
takes in the viewport and finds which pixels to color based upon the intersection
between 
*/
void Raytrace(float windowW, float windowH, Ray cameraRay, Ray lightRay);

/*** CalculateCameraRay ***/
/* 
Calculates the camera ray using the passed location of the camera and the viewport.
This function is a helper function for Raytrace.
*/
Ray CalculateCameraRay(float eyeX, float eyeY, float eyeZ, float windowW, float windowH);


/*** CalculateLightRay ***/
/*
Calculates the light ray from the camera ray and the x, y, and z values on the viewport
which we are currently mapping to. These are pixel values on the viewport calculated in
Raytrace. This function is a helper for Raytrace.
*/
Ray CalculateLightRay(float x, float y, float z,  Ray cameraRay);