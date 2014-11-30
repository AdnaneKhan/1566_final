#ifndef _PLANDRAW_H_
#define _PLANDRAW_H_

#include "common.h"
#include "plandef.hpp"

#ifndef M_PI
//Because Microsoft's compiler doesn't like pi
#define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286
#endif

#define CTR 0.50 //The center coordinate values of the sphere

//Typedef'ing function pointers? NOOOO!!! Actually, yes. This will allow
// for multiple draw styles to be used in the single drawPlanet function
typedef void(*quadDrawMethod_t)(GLfloat topLeft[3], GLfloat topRight[3],
	GLfloat bottomRight[3], GLfloat bottomLeft[3]);

//Takes care of drawing the planet based on its PTypeEnum parameter. If
// the planet's type is TEXTURED, the parameter textureName must be valid;
// otherwise (for cases like FLAT), it is unused.
void drawSelect(Planet *planet, GLuint textureName);

#endif