#include "plandraw.hpp"

static float centerVec[3] = { CTR, CTR, CTR };

static quadDrawMethod_t currentDrawMethod;

//Returns a random value from zero to one
static float randomZeroToOne(){
	return (float)rand() / ((float)RAND_MAX);
}

//Returns a random value from low to high
static float randomRangeF(float low, float high){
	return ( (high - low)*randomZeroToOne()) + low;
}

//This "bulges" the given x, y, and z away from the given center by
// a distance of "radius"
static void spherizeCoord(float centerX, float centerY, float centerZ,
						  float *x, float *y, float *z, float radius){
	//Adapted from an example on Stack Overflow:
	//http://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere

	//First, we find the change in distance along every axis
	float dx = *x - centerX;
	float dy = *y - centerY;
	float dz = *z - centerZ;

	//Then, we determine the actual distance from the center
	float distance = sqrtf(dx*dx + dy*dy + dz*dz);

	//And we change it so that the deltas are equal to the radius
	dx *= radius / distance;
	dy *= radius / distance;
	dz *= radius / distance;

	//Lastly, we set the provided x, y, and z values to their "spherized" form
	*x = centerX + dx;
	*y = centerY + dy;
	*z = centerZ + dz;
}

static void spherizeCoordv(float center[3], float point[3], float radius){
	spherizeCoord(center[0], center[1], center[2], &(point[0]), &(point[1]), &(point[2]), radius);
}

static void xyz_to_uv(float *u, float *v, float x, float y, float z){
	float unitX = x - CTR;
	float unitY = y - CTR;
	float unitZ = z - CTR;

	//First, we find the unit vector of our current vertex position
	// pointing toward the sphere's origin
	float unitMag = sqrtf(unitX*unitX+unitY*unitY+unitZ*unitZ);
	unitX /= unitMag;
	unitY /= unitMag;
	unitZ /= unitMag;

	glNormal3f(unitX, unitY, unitZ);
	
	//Then, thanks to the formula from the notes (& Wikipedia)...
	*u = 0.5 + atan2f(unitZ, unitX)/(2*M_PI);
	*v = 0.5 - asinf(unitY) / M_PI;
	
}

static void drawTextureQuad(float topLeft[3], float topRight[3],
	float bottomRight[3], float bottomLeft[3]){
	//Draws a textured quad by computing the u and v coordinates of the texture from our x, y, z
	float u = 0, v = 0;
	float u1 = 0, v1 = 0;

	//So, we convert our coordinate to UV space
	xyz_to_uv(&u, &v, topLeft[0], topLeft[1], topLeft[2]);
	//We map it to the given texture
	glTexCoord2f(u, v);
	//And draw the specified vertex with that texture coordinate
	glVertex3fv(topLeft);

	//Then, we do this for the other three vertices
	xyz_to_uv(&u1, &v1, topRight[0], topRight[1], topRight[2]);
	//However, since UV coordinates wrap around, we can get to
	// the point where we have a "belt" of the entire texture
	// compressed to a conspicuous section around x ~=0
	// Hence, we keep track of the first U,V coordinate, and we
	// check all further ones based on our "original" location
	if (u1 < 0.75 && u > 0.75)
		u1 += 1.0;
	else if (u1 > 0.75 && u < 0.75)
		u1 -= 1.0;
	glTexCoord2f(u1, v1);
	glVertex3fv(topRight);

	xyz_to_uv(&u1, &v1, bottomRight[0], bottomRight[1], bottomRight[2]);
	if (u1 < 0.75 && u > 0.75)
		u1 += 1.0;
	else if (u1 > 0.75 && u < 0.75)
		u1 -= 1.0;
	glTexCoord2f(u1, v1);
	glVertex3fv(bottomRight);

	xyz_to_uv(&u1, &v1, bottomLeft[0], bottomLeft[1], bottomLeft[2]);
	if (u1 < 0.75 && u > 0.75)
		u1 += 1.0;
	else if (u1 > 0.75 && u < 0.75)
		u1 -= 1.0;
	glTexCoord2f(u1, v1);
	glVertex3fv(bottomLeft);
}

static void drawFlatQuad(float topLeft[3], float topRight[3], 
						 float bottomRight[3], float bottomLeft[3]){
	//All this really does is draw the quad in order. It will only look spherical if used in spherizeAndDraw
	glVertex3fv(topLeft);
	glVertex3fv(topRight);
	glVertex3fv(bottomRight);
	glVertex3fv(bottomLeft);
}

static void drawCoarseGradientQuad(float topLeft[3], float topRight[3],
								   float bottomRight[3], float bottomLeft[3]){
	//This will set the quad's color equal to the top left coordinate value
	glColor3fv(topLeft);
	drawFlatQuad(topLeft, topRight, bottomRight, bottomLeft);
}

static void drawFineGradientQuad(float topLeft[3], float topRight[3],
							     float bottomRight[3], float bottomLeft[3]){
	//This takes each corner of the quad and sets its color to be equal to its coordinates
	glColor3fv(topLeft);
	glVertex3fv(topLeft);
	glColor3fv(topRight);
	glVertex3fv(topRight);
	glColor3fv(bottomRight);
	glVertex3fv(bottomRight);
	glColor3fv(bottomLeft);
	glVertex3fv(bottomLeft);
}


//This will spherize the coordinate vectors given, and then use the currentDrawMethod
static void spherizeAndDraw(float topLeft[3], float topRight[3], 
							float bottomRight[3], float bottomLeft[3], float radius){
	spherizeCoordv(centerVec, topLeft, radius);
	spherizeCoordv(centerVec, topRight, radius);
	spherizeCoordv(centerVec, bottomRight, radius);
	spherizeCoordv(centerVec, bottomLeft, radius);

	currentDrawMethod(topLeft, topRight, bottomRight, bottomLeft);
}

//This is the legitimate drawing function
static void drawThePlanet(Planet *planet){
	float i, j;

	for (i = 0; i < 1; i += planet->resolution){
		//XY
		glBegin(GL_QUADS); {
			for (j = 0; j < 1; j += planet->resolution){
				//Set the points
				GLfloat tL[] = { i, j, 0 };
				GLfloat tR[] = { i + planet->resolution, j, 0 };
				GLfloat bR[] = { i + planet->resolution, j + planet->resolution, 0 };
				GLfloat bL[] = { i, j + planet->resolution, 0 };

				//And draw them
				spherizeAndDraw(tL, tR, bR, bL, planet->radius);
			}
		}
		glEnd();
		glBegin(GL_QUADS); {
			for (j = 0; j < 1; j += planet->resolution){
				//And so on
				GLfloat tL[] = { i, j, 1 };
				GLfloat tR[] = { i + planet->resolution, j, 1 };
				GLfloat bR[] = { i + planet->resolution, j + planet->resolution, 1 };
				GLfloat bL[] = { i, j + planet->resolution, 1 };

				//And so forth
				spherizeAndDraw(tL, tR, bR, bL, planet->radius);
			}
		}
		glEnd();

		//XZ (perhaps texture in xzy order)
		glBegin(GL_QUADS); {
			for (j = 0; j < 1; j += planet->resolution){
				GLfloat tL[] = { i, 0, j };
				GLfloat tR[] = { i + planet->resolution, 0, j };
				GLfloat bR[] = { i + planet->resolution, 0, j + planet->resolution };
				GLfloat bL[] = { i, 0, j+planet->resolution };

				spherizeAndDraw(tL, tR, bR, bL, planet->radius);
			}
		}
		glEnd();
		glBegin(GL_QUADS); {
			for (j = 0; j < 1; j += planet->resolution){
				GLfloat tL[] = { i, 1, j };
				GLfloat tR[] = { i + planet->resolution, 1, j };
				GLfloat bR[] = { i + planet->resolution, 1, j + planet->resolution };
				GLfloat bL[] = { i, 1, j + planet->resolution };

				spherizeAndDraw(tL, tR, bR, bL, planet->radius);
			}
		}
		glEnd();

		//YZ (maybe texture in zyx order)
		glBegin(GL_QUADS); {
			for (j = 0; j < 1; j += planet->resolution){
				GLfloat tL[] = { 0, i, j };
				GLfloat tR[] = { 0, i + planet->resolution, j };
				GLfloat bR[] = { 0, i + planet->resolution, j + planet->resolution };
				GLfloat bL[] = { 0, i, j + planet->resolution };

				spherizeAndDraw(tL, tR, bR, bL, planet->radius);
			}
		}
		glEnd();
		glBegin(GL_QUADS); {
			for (j = 0; j < 1; j += planet->resolution){
				GLfloat tL[] = { 1, i, j };
				GLfloat tR[] = { 1, i + planet->resolution, j };
				GLfloat bR[] = { 1, i + planet->resolution, j + planet->resolution };
				GLfloat bL[] = { 1, i, j + planet->resolution };

				spherizeAndDraw(tL, tR, bR, bL, planet->radius);
			}
		}
		glEnd();
	}


}

//What drawSelect actually does is just set up the function pointer
// to be used in our drawThePlanet function
void drawSelect(Planet * planet, GLuint textureName){
	int usingTex = FALSE;

	switch (planet->planetType){
	case STAR:
		//If we're using textures, we need to set them up
		usingTex = TRUE;
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		glBindTexture(GL_TEXTURE_2D, textureName);

		//And, we set our drawing function to that of our texture function
		currentDrawMethod = &drawTextureQuad;
		break;
	case TEXTURED:
		//If we're using textures, we need to set them up
		usingTex = TRUE;
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, textureName);

		//And, we set our drawing function to that of our texture function
		currentDrawMethod = &drawTextureQuad;
		break;
	case FLAT:
		//For FLAT, we don't care about textures, so we can just setup our pointer
		currentDrawMethod = &drawFlatQuad;
		break;
	case COARSE_GRADIENT:
		//... and so on for the rest of them
		currentDrawMethod = &drawCoarseGradientQuad;
		break;
	case FINE_GRADIENT:
		currentDrawMethod = &drawFineGradientQuad;
		break;

	default:
		printf("Unsupported planet type (%d): draw aborted\n", planet->planetType);
		return;
	}
	glPushMatrix(); {
		drawThePlanet(planet);
	}glPopMatrix();

	if (usingTex == TRUE){
		//And, if we happened to be using textures, we need to remember to disable them
		glDisable(GL_TEXTURE_2D);
	}
}