#ifndef PLANETFOLLOWER_H
#define PLANETFOLLOWER_H

#include "common.h"
#include "Planetary_System.hpp"
#include "Planetary_Body.hpp"
#include "Space_Object.hpp"
#include "Math_helper.hpp"
#include <vector>
#include <deque>

class Planetfollower {
public:	
	Planetary_System *system;
	Space_Object *currentPlanet;
	Space_Object *currentSatellite;

	std::deque<Space_Object *> listOfPlanets;
	std::deque<Space_Object *> listOfSatellites;

	int planet;
	int satellite;
	int planetOrSatellite;

	float camera_pos[3];
	float up_vec[3];
	float looking_at[3];

	/*** Planetfollower ***/
	/*
	Creates object that follows planets in the system.
	*/
	Planetfollower(){};
	Planetfollower(Planetary_System *root);

	void Planetfollower::SetSolarSystem(Planetary_System *root);

	/*** SwitchPlanet ***/
	/*
	Changes the planet based on the flag passed, either 1, -1, or 0.
	 1: changes to next planet (or loops to beginning)
	-1: changes to previous planet (or loops to end)
	 0: remains on planet
	*/
	void Planetfollower::SwitchPlanet(int flag);

	/*** ChangeToSatellite ***/
	/*
	If Satellite exists, changes to the satellite around the current
	planet.
	*/
	void Planetfollower::ChangeToPlanet();

	/*** ChangeToSatellite ***/
	/*
	If Satellite exists, changes to the satellite around the current
	planet.
	*/
	void Planetfollower::ChangeToSatellite();

	/*** InitializeCamera ***/
	/*
	Initializes camera around planet.
	*/
	void Planetfollower::InitializeCamera();

	/*** UpdateCamera ***/
	/*
	Updates the the camera position.
	*/
	void Planetfollower::UpdateCamera();

	/*** MoveCamera ***/
	/*
	Calls gluLookAt() to move the camera.
	*/
	void Planetfollower::MoveCamera();
};

#endif