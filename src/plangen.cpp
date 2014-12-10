#include "plangen.hpp"
#include "plandraw.hpp"

void createPlanet(Planet * planet, PTypeEnum drawType, GLfloat radius, GLfloat resolution){
	//First, we ensure that the input pointer is NULL, so we don't overwrite anyting
	/*if (planet != NULL){
		puts("Planet cannot be created: input pointer may be valid");
		return;
	}*/
	//Now, we need to check the radius for validity
	if (radius <= 0){
		printf("Invalid radius (%f): must be greater than zero\n", radius);
		return;
	}
	//And the resolution, too
	if (resolution <= 0 || resolution >= 1){
		printf("Invalid resolution (%f): must be in the range (0, 1)\n", resolution);
		return;
	}

	//At this point, we know we have a valid set of arguments
//	planet = (Planet*)malloc(sizeof(Planet));
	//We may hereby set the members of our data structure
	planet->planetType = drawType;
	planet->radius = radius;
	planet->resolution = resolution;
}

void drawPlanet(Planet *planet, GLuint optionalTexture, float world_pos[3], int planet_radius){
	drawSelect(planet, optionalTexture, world_pos, planet_radius);
}