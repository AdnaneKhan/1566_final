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
	
	void set_ui_color(int color);

	void draw_interface(float velocity_mag, int mousex, int mousey, GLfloat roll);

	void set_window_parameters(int height, int width);

private:


	int window_height;
	int window_width;

	void reticular_translate(int x, int y);

};


#endif // END USER_INTERFACE_H GUARD