#include "Planetfollower.hpp"

Planetfollower::Planetfollower(Planetary_System *root) {
	this->system = root;
	listOfPlanets = root->orbiting_planets();
	currentPlanet = listOfPlanets.front();
	listOfSatellites = currentPlanet->satellites;
	if (currentPlanet->num_satellites() != 0) {
		currentSatellite = listOfSatellites.front();
	}
	planetOrSatellite = 0;
}

void Planetfollower::SetSolarSystem(Planetary_System *root) {
	this->system = root;
	listOfPlanets = root->orbiting_planets();
	currentPlanet = listOfPlanets.front();
	listOfSatellites = currentPlanet->satellites;
	if (currentPlanet->num_satellites() != 0) {
		currentSatellite = listOfSatellites.front();
	}
	planetOrSatellite = 0;
}

void Planetfollower::SwitchPlanet(int flag) {
	if (flag == 1) {
		planet += flag;
		if (planet == listOfPlanets.size()) {
			planet = 0;
		}
		currentPlanet = listOfPlanets[planet];
	}
	else if (flag == -1) {
		planet += flag;
		if (planet == -1) {
			planet = listOfPlanets.size() - 1;
		}
		currentPlanet = listOfPlanets[planet];
	}
}

void Planetfollower::ChangeToPlanet() {
	planetOrSatellite = 0;
}

void Planetfollower::ChangeToSatellite() {
	planetOrSatellite = 1;
}

void Planetfollower::InitializeCamera() {
	float line_to_object[3];
	//float signVector[3];
	float lineMag;
	if (planetOrSatellite == 0) {
		for (int i = 0; i < 3; i++) {
			line_to_object[i] = currentPlanet->world_pos[i];
			//signVector[i] = line_to_object[i] / line_to_object[i];
		}
		lineMag = sqrt(pow(line_to_object[0], 2) + pow(line_to_object[1], 2) + pow(line_to_object[2], 2));
		for (int i = 0; i < 3; i++) {
			camera_pos[i] = (line_to_object[i] + ((line_to_object[i] / lineMag)*(currentPlanet->get_radius() * 15)));
			looking_at[i] = 0;
			//looking_at[i] = currentPlanet->world_pos[i];
			up_vec[i] = currentPlanet->get_orbital_plane().planeNormal[i];
			printf("%f", up_vec[i]);
		}
		printf("\n");
		//camera_pos[2] += 50;
	}
	/*else if (planetOrSatellite == 1) {
		for (int i = 0; i < 3; i++) {
			line_to_object[i] = currentSatellite->world_pos[i];
		}
		lineMag = sqrt(pow(line_to_object[0], 2) + pow(line_to_object[1], 2) + pow(line_to_object[2], 2));
		for (int i = 0; i < 3; i++) {
			camera_pos[i] = line_to_object[i] + ((line_to_object[i] / lineMag) * (currentSatellite->get_radius() * 15));
			looking_at[i] = 0;
			//looking_at[i] = currentSatellite->world_pos[i];
			//up_vec[i] = currentSatellite->get_orbital_plane().planeNormal[i];
		}
		up_vec[0] = 0;
		up_vec[1] = 0;
		up_vec[2] = 1;
		//camera_pos[2] += 50;
	}*/
}

void Planetfollower::UpdateCamera() {

}

void Planetfollower::MoveCamera() {
	gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2],
			  looking_at[0], looking_at[1], looking_at[2], 
			  up_vec[0], up_vec[1], up_vec[2]);
}