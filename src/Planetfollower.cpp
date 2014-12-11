#include "Planetfollower.hpp"

Planetfollower::Planetfollower(Planetary_System *root) {
	this->system = root;
	listOfPlanets = root->orbiting_planets();
	currentPlanet = listOfPlanets.front();
	if (currentPlanet->num_satellites() != 0) {
		currentSatellite = currentPlanet->satellites.back();
	}
	planetOrSatellite = 0;
}

void Planetfollower::SetSolarSystem(Planetary_System *root) {
	this->system = root;
	listOfPlanets = root->orbiting_planets();
	currentPlanet = listOfPlanets.front();
	if (currentPlanet->num_satellites() != 0) {
		currentSatellite = currentPlanet->satellites.front();
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
	if (currentPlanet->num_satellites() != 0) {
		currentSatellite = currentPlanet->satellites.back();
	}
}

void Planetfollower::ChangeToPlanet() {
	planetOrSatellite = 0;
	planetTheta = 0;
}

void Planetfollower::ChangeToSatellite() {
	planetOrSatellite = 1;
	currentSatellite = currentPlanet->satellites.front();
	planetTheta = 0;
}

void Planetfollower::ChangeToGlobal() {
	localOrGlobal = 1;
	planetTheta = 0;
}

void Planetfollower::ChangeToLocal() {
	localOrGlobal = 0;
	planetTheta = 0;
}

void Planetfollower::UpdateCamera() {
	float line_to_object[3];
	float lineMag;
	up_vec[0] = 0;
	up_vec[1] = 0;
	up_vec[2] = 1;

	if (localOrGlobal == 0) {
		if (planetOrSatellite == 0) {
			for (int i = 0; i < 3; i++) {
				line_to_object[i] = currentPlanet->world_pos[i];
			}
			rot_vector((M_PI/180)*planetTheta, 0, 0, 1, line_to_object);
			lineMag = sqrt(pow(line_to_object[0], 2) + pow(line_to_object[1], 2) + pow(line_to_object[2], 2));
			camera_pos[0] = currentPlanet->world_pos[0] + ((line_to_object[0] / lineMag) * (currentPlanet->get_radius() * 15));
			camera_pos[1] = currentPlanet->world_pos[1] + ((line_to_object[1] / lineMag) * (currentPlanet->get_radius() * 15));
			camera_pos[2] = currentPlanet->world_pos[2] + ((line_to_object[2] / lineMag) * (currentPlanet->get_radius() * 15));
			for (int i = 0; i < 3; i++) {
				//camera_pos[i] = line_to_object[i] + (((line_to_object[i] / lineMag) * (currentPlanet->get_radius() * 15)));
				looking_at[i] = currentPlanet->world_pos[i];
				//up_vec[i] = currentPlanet->get_orbital_plane().planeNormal[i];
			}
		}
		else if (planetOrSatellite == 1) {
			for (int i = 0; i < 3; i++) {
				line_to_object[i] = currentSatellite->world_pos[i]-currentPlanet->world_pos[i];
			}
			rot_vector((M_PI / 180)*planetTheta, 0, 0, 1, line_to_object);
			lineMag = sqrt(pow(line_to_object[0], 2) + pow(line_to_object[1], 2) + pow(line_to_object[2], 2));
			for (int i = 0; i < 3; i++) {
				camera_pos[i] = currentSatellite->world_pos[i] + ((line_to_object[i] / lineMag) * (currentSatellite->get_radius() * 15));
				looking_at[i] = currentSatellite->world_pos[i];
				//up_vec[i] = currentSatellite->get_orbital_plane().planeNormal[i];
			}
		}
	}
	else if (localOrGlobal == 1) {
		up_vec[0] = 0;
		up_vec[1] = 0;
		up_vec[2] = 1;

		camera_pos[0] = 0;
		camera_pos[1] = 0;
		camera_pos[2] = system->star->get_radius()+200;
		
		if (planetOrSatellite == 0) {
			for (int i = 0; i < 3; i++) {
				looking_at[i] = currentPlanet->world_pos[i];
			}
		}
		else if (planetOrSatellite == 1) {
			for (int i = 0; i < 3; i++) {
				looking_at[i] = currentSatellite->world_pos[i];
			}
		}
	}
}

void Planetfollower::RotateCamera() {

}

void Planetfollower::MoveCamera() {
	gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2],
			  looking_at[0], looking_at[1], looking_at[2], 
			  up_vec[0], up_vec[1], up_vec[2]);
	printf("%f,%f,%f\n%f,%f,%f\n%f,%f,%f\n\n", camera_pos[0], camera_pos[1], camera_pos[2],
		looking_at[0], looking_at[1], looking_at[2],
		up_vec[0], up_vec[1], up_vec[2]);
}
