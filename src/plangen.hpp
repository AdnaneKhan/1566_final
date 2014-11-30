#ifndef _PLANGEN_H_
#define _PLANGEN_H_

#include "common.h"
#include "plandef.hpp"

//Returns a newly allocated pointer to a planet struct
// Parameter resolution must be between (0, 1)
void createPlanet(Planet *planet, PTypeEnum drawType, GLfloat radius, GLfloat resolution);

//Draws the given planet
void drawPlanet(Planet *planet, GLuint optionalTexture);

//Frees the given planet
void freePlanet(Planet *planet);

#endif