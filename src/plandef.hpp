#ifndef _PLANDEF_H_
#define _PLANDEF_H_

//This header file solely contains the definition of the
// planet struct and its related enumerated type

#define NUM_PTYPES 4

typedef enum planet_type_specifier {
	TEXTURED, FLAT, COARSE_GRADIENT, FINE_GRADIENT,STAR
} PTypeEnum;

typedef struct planet_struct {
	PTypeEnum planetType;
	float radius;		//Must be greater than zero
	float resolution; //Must be in the range (0, 1)
} Planet;

#endif