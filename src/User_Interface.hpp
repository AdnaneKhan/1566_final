#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

class User_Interface {
public:


	// Handles click from mouse and responds with appropraite
	// User interface functiality of the coordinates match any UI elements
	void handle_mouse_click(int x, int y, int win_h,int win_w);
	

	void draw_interface(float velocity_mag);

private:
	// Sets the projection matrix to ortho 2d to facilitate drawing of 2D interface
	//void set_2d();

	// Reverts to proper 3D perspective projection
	//void revert_3d();

	void draw_init_menu();

	void draw_game_ui();



};


#endif // END USER_INTERFACE_H GUARD