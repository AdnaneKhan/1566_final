#include "Planetary_System.hpp"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Spaceship.hpp"		
#include "User_Interface.hpp"
#include "Spacebox.hpp"

#define min(a,b) ((a) < (b)? a:b)
#define FALSE 0 
#define TRUE  1

#define COUNTERCLOCKWISE  1
#define CLOCKWISE -1

#define DELTA_TIME 15
#define DELTA_DEG  1

#define WINDOW_HEIGHT 1024
#define WINDOW_WIDTH 1024

GLfloat vertices[][3] = {
	{ -1, 1, 1 }, { 1, 1, 1 }, { 1, 1, -1 }, { -1, 1, -1 },
	{ -1, -1, 1 }, { 1, -1, 1 }, { 1, -1, -1 }, { -1, -1, -1 }
};

void glut_setup(void);
void gl_setup(void);
void my_setup(void);
void lighting_setup();
void my_display(void);
void my_reshape(int w, int h);
void my_keyboard(unsigned char key, int x, int y);
void mouse_control(int x, int y);

void time_update(int param);

int win_h;
int win_w;


Planetary_System * root;
Texture * all_space;
Spaceship ship;
User_Interface ui;
Spacebox * box;

int main(int argc, char **argv) {

	/* General initialization for GLUT and OpenGL
	Must be called first */
	glutInit(&argc, argv);


	/* we define these setup procedures */
	glut_setup();
	gl_setup();
	my_setup();

	/* go into the main event loop */
	glutMainLoop();

	return(0);
}

/* This function sets up the windowing related glut calls */
void glut_setup(void) {

	/* specify display mode -- here we ask for a double buffer and RGB coloring */
	/* NEW: tell display we care about depth now */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	/* make a 400x400 window with the title of "GLUT Skeleton" placed at the top left corner */
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	win_h = WINDOW_HEIGHT;
	win_w = WINDOW_WIDTH;
	glutInitWindowPosition(0, 0);
	glutCreateWindow("SPACE");


	glutDisplayFunc(my_display);
	glutReshapeFunc(my_reshape);
	glutKeyboardFunc(my_keyboard);
	glutPassiveMotionFunc(mouse_control);
	return;
}

/* This function sets up the initial states of OpenGL related enivornment */
void gl_setup(void) {
	
	/* specifies a background color: black in this case */
	glClearColor(0, 0, 0, 0);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, 1.0, 1.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* NEW: lighting stuff */
	glShadeModel(GL_SMOOTH);
	glutTimerFunc(100, time_update, 0);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	return;
}

void my_setup(void) {

	root = new Planetary_System(50.0, 1);
	all_space = new Texture("textures/skybox.bmp", 256, 256);
	box = new Spacebox(1.0, all_space, all_space, all_space, all_space, all_space, all_space);

	lighting_setup();
	return;
}

void my_reshape(int w, int h) {

	win_w = min(w, h);
	win_h = min(w, h);

	/* define viewport -- x, y, (origin is at lower left corner) width, height */
	glViewport(0, 0, win_w, win_h);
	return;
}

void my_keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'w':
		ship.update_velocity(DEFAULT_SPEED_DELTA);
		
		break;
	case 'a':
		ship.look_left(DEFAULT_LOOK_DELTA);
		break;
	case 's':
		ship.update_velocity(-DEFAULT_SPEED_DELTA);

		break; 
	case 'd':
		ship.look_right(DEFAULT_LOOK_DELTA);
		break;
	case 'e': 
		ship.roll_right(DEFAULT_LOOK_DELTA);
		break;
	case ' ':
		ship.stop_ship();
		break;
	case 'q':
		ship.roll_left(DEFAULT_LOOK_DELTA);
			break;
	case 'Q':
		delete (all_space);
		//delete(box);
		delete(root);
		exit(0);
	default: break;
	}
	return;
}


void mouse_control( int x, int y) {
	// Deadzones for X and Y
	ship.mouse_control(x, y,win_h,win_w);
}

void lighting_setup() {

	GLfloat light0_amb[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat light0_diffuse[] = { 1, 1, 1, 1 };
	GLfloat light0_specular[] = { .4, .4, .4, 1 };

	GLfloat globalAmb[] = { 0, 0, 0, 1 };

	GLfloat no_mat[] = { 0, 0, 0, 1 };
	GLfloat mat_amb_diff[] = { .1, .5, .8, 1 };
	GLfloat mat_specular[] = { 1, 1, 1, 1 };
	GLfloat mat_no_shininess[] = { 0 };
	GLfloat mat_low_shininess[] = { 2.5 };
	GLfloat mat_high_shininess[] = { 100 };
	GLfloat mat_emission[] = { .3, .2, .2, 0 };

	//enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	// setup properties of point light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	// reflective propoerites -- global ambiant light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

	// setup material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb_diff);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_amb_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_low_shininess);

}

void my_display(void) {
	GLfloat light0_pos[] = { 0, 0, 0, 1 };

	/* clear the buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
//	glLightfv(this->light_id, GL_SPOT_DIRECTION, this->look_dir);
//	glLighti(this->light_id, GL_SPOT_CUTOFF, this->look_angle);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat ship_pos[3];


	// Gets position of ship
	ship.get_position(ship_pos);

	// Draws Skybox
	box->draw_skybox(ship_pos);
	// Draw HUD
	ui.draw_interface(ship.get_velocity());
	
	// Sets the Camera
	ship.set_camera();

	root->draw_system();

	/* buffer is ready */
	glutSwapBuffers();
	glutPostRedisplay();
	return;
}

void time_update(int param) {
	
	ship.update();
	root->update_system();
	glutTimerFunc(DELTA_TIME, time_update, 0);
}