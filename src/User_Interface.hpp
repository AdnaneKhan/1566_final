#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

namespace User_Interface {
	static void keyboard_interface(unsigned char key, int x, int y);

	static void mouse_interface(int pressed, int x, int y);

}


#endif // END USER_INTERFACE_H GUARD