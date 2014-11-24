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

#define min(a,b) ((a) < (b)? a:b)
#define FALSE 0 
#define TRUE  1

#define COUNTERCLOCKWISE  1
#define CLOCKWISE -1

#define DELTA_TIME 5
#define DELTA_DEG  5

int   light1_theta = 0;
float zoom = 1.0;

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

Planetary_System root(100.0, 2);
Spaceship ship;

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
	glutInitWindowSize(1024, 1024);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Lights");


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
	gluPerspective(40, 1.0, 1.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* NEW: lighting stuff */
	glShadeModel(GL_SMOOTH);
	glutTimerFunc(100, time_update, 0);
	return;
}

void my_setup(void) {
	lighting_setup();
	return;
}

void my_reshape(int w, int h) {

	/* define viewport -- x, y, (origin is at lower left corner) width, height */
	glViewport(0, 0, min(w, h), min(w, h));
	return;
}

void my_keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'z':

		ship.update_velocity(DEFAULT_SPEED_DELTA);
		break;
	case 'x':
		ship.update_velocity(-DEFAULT_SPEED_DELTA);
		break;
	case 'w':
		ship.look_up(-DEFAULT_LOOK_DELTA);
		break;
	case 'a':
		ship.look_left(DEFAULT_LOOK_DELTA);
		break;
	case 's':
		ship.look_down(DEFAULT_LOOK_DELTA);
		break;
	case 'd':
		ship.look_right(DEFAULT_LOOK_DELTA);
		break;
	case 'e': 
		ship.roll_right(DEFAULT_LOOK_DELTA);
		break;
	case 'q':
		ship.roll_left(DEFAULT_LOOK_DELTA);
			break;
	case 'Q':
		exit(0);
	default: break;
	}
	return;
}


void mouse_control( int x, int y) {
	GLfloat turn_vector[2];

	if ((x > 0 && x < 1024) && (y > 0 && y < 1024)) {
		turn_vector[X] = (x - 1024 / 2);
		turn_vector[Y] = (y - 1024 / 2);

		ship.look_right(turn_vector[X]/1024 * DEFAULT_LOOK_DELTA);
		ship.look_up(turn_vector[Y]/1024 * DEFAULT_LOOK_DELTA);
			
	}
}

void lighting_setup() {

	GLfloat light0_amb[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat light0_diffuse[] = { 1, 0, 0, 1 };
	GLfloat light0_specular[] = { 1, 0, 0, 1 };
	GLfloat light0_pos[] = { 1, 1, 1, 0 };

	GLfloat light1_amb[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat light1_diffuse[] = { 0, 1, 0, 1 };
	GLfloat light1_specular[] = { 0, 1, 0, 1 };

	GLfloat globalAmb[] = { .1, .1, .1, 1 };

	GLfloat no_mat[] = { 0, 0, 0, 1 };
	GLfloat mat_amb_diff[] = { .1, .5, .8, 1 };
	GLfloat mat_specular[] = { 1, 1, 1, 1 };
	GLfloat mat_no_shininess[] = { 0 };
	GLfloat mat_low_shininess[] = { 5 };
	GLfloat mat_high_shininess[] = { 100 };
	GLfloat mat_emission[] = { .3, .2, .2, 0 };

	//enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//  glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	// setup properties of point light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	// reflective propoerites -- global ambiant light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

	// setup material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb_diff);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_amb_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_high_shininess);

}

void my_display(void) {
	GLfloat light1_pos[] = { -1, 1, 1, 0 };
	GLfloat light1_dir[] = { 0, 0, 1 };

	/* clear the buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	ship.set_camera();

	glColor3f(0, .2, 1);
	root.draw_system();

	glPushMatrix();



	glScalef(200,200, 1);
	glTranslatef(0, 0, -5);
	glColor3f(.0, .0, .0);
	//glutSolidCube(1);

	glPopMatrix();


	
	// do transformation for light1 -- should have no effect on anything else
	glPushMatrix();
	{
		glRotatef(light1_theta, 0, 1, 0);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);

		// visual aid: draw a box to show where the light is at 
		glTranslatef(-1, 1, 1);
		glutSolidCube(0.1);
	}
	glPopMatrix();

	

	/* buffer is ready */
	glutSwapBuffers();
	glutPostRedisplay();
	return;
}

void time_update(int param) {
	ship.update();
	root.update_system();
	glutTimerFunc(DELTA_TIME, time_update, 0);
}