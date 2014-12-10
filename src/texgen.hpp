#ifndef _TEXGEN_H_
#define _TEXGEN_H_

#define NUM_DYNAMIC_TEXTURES 5
#define NUM_TEXTURES 6
#define EARTHY_TEX   0
#define ICEY_TEX    1
#define BADLAND_TEX 2
#define MOON_TEX 3
#define TURB_RED 4

#define IMG_WIDTH 1024
#define IMG_HEIGHT 1024
#define MAX_WALKERS 32

//These types of methods define an equation whose input is a "height"
// value from 0 to 255. Here, the parameters r, g, and b will be set
// according to the underlying implementation
typedef void(*triGradientMethod_t)(unsigned char height,
	unsigned char *r, unsigned char *g, unsigned char *b);

//This will fill "destination" with a Brownian (random particle) walk to
// simulate the appearance of land. The particle will randomly walk
// and increment the height parameter (which is the last element of the
// third dimension, i.e., destination[i][j][3]). Then, the "drawMethod"
// will set the values accordingly. The resultant array can be used in
// the setup method for a 2D texture
void brownian(unsigned char destination[IMG_HEIGHT][IMG_WIDTH][4],
	triGradientMethod_t drawMethod, long numSteps);

void multiBrown(unsigned char dest[IMG_HEIGHT][IMG_WIDTH][4], triGradientMethod_t drawMethod,
	long numPoints, int numWalkers);

//This will randomly walk the destination array with a bias toward
// horizontal movement, and it will set the colors accordingly.
void scanLines(unsigned char destination[IMG_HEIGHT][IMG_WIDTH][4],
	triGradientMethod_t drawMethod, long numSteps);

void multiScan(unsigned char dest[IMG_HEIGHT][IMG_WIDTH][4], triGradientMethod_t drawMethod,
	long numPoints, int numWalkers);

#endif