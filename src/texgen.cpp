#include "common.h"
#include "texgen.hpp"

static void texInit(unsigned char destination[IMG_HEIGHT][IMG_WIDTH][4]){
	int i, j;
	//Setup the initial (zeroed) height values
	for (i = 0; i < IMG_HEIGHT; i++){
		for (j = 0; j < IMG_WIDTH; j++) {
			destination[i][j][3] = 0;
		}
	}
}

static void texApplyGradient(unsigned char destination[IMG_HEIGHT][IMG_WIDTH][4],
	triGradientMethod_t drawMethod){
	int i, j;
	//Set all the values in the array according to the height mapping
	for (i = 0; i < IMG_HEIGHT; i++){
		for (j = 0; j < IMG_WIDTH; j++){
			drawMethod(destination[i][j][3],
				&(destination[i][j][0]), &(destination[i][j][1]), &(destination[i][j][2]));
		}
	}
}

static void randomWalk(unsigned char destination[IMG_HEIGHT][IMG_WIDTH][4],
	triGradientMethod_t drawMethod, long numSteps,
	int upWeight, int downWeight, int rightWeight, int nWalkers){
	//This method encapsulates all the brownian-type generators, specialized
	// to allow for custom directonal biases
	int walkerI[MAX_WALKERS], walkerJ[MAX_WALKERS];
	int w = 0;
	int toggle = 1;	//This will be used to toggle the direction

	//Setup the initial (zeroed) height values
	texInit(destination);

	//Initialize the walkers to a random position
	for (w = 0; w < nWalkers && w < MAX_WALKERS; w++){
		walkerI[w] = rand() % IMG_HEIGHT;
		walkerJ[w] = rand() % IMG_WIDTH;
	}

	//Then, randomly walk for as long as has been specified
	while (numSteps > 0){
		for (w = 0; w < nWalkers && w < MAX_WALKERS; w++){
			toggle = rand();

			if (toggle < upWeight){
				walkerI[w]++;
			}
			else if (toggle < downWeight){
				walkerI[w]--;
			}
			else if (toggle < rightWeight){
				walkerJ[w]++;
			}
			else{
				walkerJ[w]--;
			}
			walkerI[w] = (walkerI[w] + IMG_HEIGHT) % IMG_HEIGHT;
			walkerJ[w] = (walkerJ[w] + IMG_WIDTH) % IMG_WIDTH;

			destination[walkerI[w]][walkerJ[w]][3] ++;
		}
		numSteps--;
	}

	//Lastly, set the r, g, and b values:
	texApplyGradient(destination, drawMethod);
}

void multiBrown(unsigned char dest[IMG_HEIGHT][IMG_WIDTH][4], triGradientMethod_t drawMethod,
	long numPoints, int numWalkers){
	randomWalk(dest, drawMethod, numPoints, (RAND_MAX / 4), (RAND_MAX / 2), ((RAND_MAX / 4) * 3), numWalkers);
}

void brownian(unsigned char destination[IMG_HEIGHT][IMG_WIDTH][4],
	triGradientMethod_t drawMethod, long numPoints){
	//All we do here is give our randomWalk function equally spaced weights

	multiBrown(destination, drawMethod, numPoints, 1);
}

void multiScan(unsigned char dest[IMG_HEIGHT][IMG_WIDTH][4], triGradientMethod_t drawMethod,
	long numPoints, int numWalkers){
	randomWalk(dest, drawMethod, numPoints, RAND_MAX / 8, RAND_MAX / 4, RAND_MAX / 2, numWalkers);
}

void scanLines(unsigned char destination[IMG_HEIGHT][IMG_WIDTH][4],
	triGradientMethod_t drawMethod, long numPoints){
	//We simply call randomWalk with a greater bias toward horizontal movement
	multiScan(destination, drawMethod, numPoints, 1);
}