#include "User_Interface.hpp"

void User_Interface::keyboard_interface(unsigned char key, int x, int y) {

	switch (key) {
	case 'q':
	case 'Q':
		exit(0);
	default: break;
	}
	return;
}