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
						int upWeight, int downWeight, int rightWeight){
	//This method encapsulates all the brownian-type generators, specialized
	// to allow for custom directonal biases
	int i = 0, j = 0;

	int toggle = 1;	//This will be used to toggle the direction

	//Setup the initial (zeroed) height values
	texInit(destination);

	//Then, randomly walk for as long as has been specified
	while (numSteps > 0){
		toggle = rand();

		if (toggle < upWeight){
			i++;
		}
		else if (toggle < downWeight){
			i--;
		}
		else if (toggle < rightWeight){
			j++;
		}
		else{
			j--;
		}
		i = (i + IMG_HEIGHT) % IMG_HEIGHT;
		j = (j + IMG_WIDTH) % IMG_WIDTH;

		destination[i][j][3] ++;
		numSteps--;
	}

	//Lastly, set the r, g, and b values:
	texApplyGradient(destination, drawMethod);
}


void brownian(unsigned char destination[IMG_HEIGHT][IMG_WIDTH][4],
					triGradientMethod_t drawMethod, long numPoints){
	//All we do here is give our randomWalk function equally spaced weights
	randomWalk(destination, drawMethod, numPoints, (RAND_MAX / 4), (RAND_MAX / 2), ((RAND_MAX/4)*3) );
}

void scanLines(unsigned char destination[IMG_HEIGHT][IMG_WIDTH][4],
					triGradientMethod_t drawMethod, long numPoints){
	//We simply call randomWalk with a greater bias toward horizontal movement
	randomWalk(destination, drawMethod, numPoints, RAND_MAX / 8, RAND_MAX / 4, RAND_MAX / 2);
}