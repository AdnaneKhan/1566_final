#include "User_Interface.hpp"

int _COLOR = 0;
int shipForwardSpeed = 0;
int shipBackwardSpeed = 0;
float old_mag = 0.0;

void User_Interface::set_ui_color(int color)
{
	_COLOR = color;
}

void set_color()
{
	switch (_COLOR) 
	{
		case 0:
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
		case 1:
			glColor3f(0.0f, 1.0f, 0.0f);
			break;
		case 2:
			glColor3f(0.0f, 0.0f, 1.0f);
			break;
		default: 
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
	}
	return;
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius)
{
	int i;
	int lineAmount = 360; //# of triangles used to draw circle
	
	GLfloat twicePi = 2.0f * 3.14159265359;
	
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

void drawHollowSemiCircle(GLfloat x, GLfloat y, GLfloat radius, int start, int end)
{
	int i;
	int j;
	int lineAmount = 360; //# of triangles used to draw circle	

	GLfloat twicePi = 2.0f * 3.14159265359;
	
	if (start > end)
	{
		start -= 360;
	}

	glPushMatrix();
	for(i = start; i < end; i ++) 
	{ 
		j = i + 1;
		glBegin(GL_LINES);
		{
			glVertex2f(x + (radius * cos(i *  twicePi / lineAmount)), y + (radius* sin(i * twicePi / lineAmount)));
			glVertex2f(x + (radius * cos(j *  twicePi / lineAmount)), y + (radius* sin(j * twicePi / lineAmount)));
		}
		glEnd();
	}
	glPopMatrix();
	
}

void drawSpeedGage_Backward(GLfloat x, GLfloat y, float start, float end)
{
	float i;
	int lineAmount = 360; //# of triangles used to draw circle	

	GLfloat twicePi = 2.0f * 3.14159265359;

	glPushMatrix();
	glBegin(GL_POLYGON);
	{
		for(i = end; i >= start; i --) 
		{ 		
				glVertex2f(x + (7.0 * cos(i *  twicePi / lineAmount)), y + (7.0* sin(i * twicePi / lineAmount)));			
		}
		i = 0;
		for(i = start; i <= end; i ++) 
		{ 		
				glVertex2f(x + (6.5 * cos(i *  twicePi / lineAmount)), y + (6.5* sin(i * twicePi / lineAmount)));			
		}
	}
	glEnd();
	glPopMatrix();
	
}

/* Number Functions */
void draw_zero()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.0);
			glVertex2f(0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.5);
			glVertex2f(-0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.5);
			glVertex2f(-0.25, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.0);
			glVertex2f(0.25, 0.0);
		}
		glEnd();
	}
	glPopMatrix();
}

void draw_one()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.0);
			glVertex2f(0.25, 0.5);
		}
		glEnd();
	}
	glPopMatrix();
}

void draw_two()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.5);
			glVertex2f(0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.5);
			glVertex2f(0.25, 0.25);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.25);
			glVertex2f(-0.25, 0.25);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.25);
			glVertex2f(-0.25, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.0);
			glVertex2f(0.25, 0.0);
		}
		glEnd();
	}
	glPopMatrix();
}

void draw_three()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.0);
			glVertex2f(0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.5);
			glVertex2f(-0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.25);
			glVertex2f(-0.25, 0.25);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.0);
			glVertex2f(-0.25, 0.0);
		}
		glEnd();
	}
	glPopMatrix();
		
}

void draw_four()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.0);
			glVertex2f(0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.5);
			glVertex2f(-0.25, 0.25);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.25);
			glVertex2f(0.25, 0.25);
		}
		glEnd();
	}
	glPopMatrix();
}

void draw_five()
{
	glPushMatrix();
	{
		glTranslatef(0.0,0.25,0.0);
		glRotatef(180,1,0,0);
		glTranslatef(0.0,-0.25,0.0);
		draw_two();
	}
	glPopMatrix();
}

void draw_six()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.0);
			glVertex2f(0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.25);
			glVertex2f(0.25, 0.25);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.0);
			glVertex2f(0.25, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.25);
			glVertex2f(-0.25, 0.0);
		}
		glEnd();
	}
	glPopMatrix();
}

void draw_seven()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.0);
			glVertex2f(0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.5);
			glVertex2f(-0.25, 0.5);
		}
		glEnd();
	}
	glPopMatrix();
}

void draw_eight()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.0);
			glVertex2f(0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.5);
			glVertex2f(-0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.5);
			glVertex2f(-0.25, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.0);
			glVertex2f(0.25, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.25);
			glVertex2f(0.25, 0.25);
		}
		glEnd();
	}
	glPopMatrix();
}

void draw_nine()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.0);
			glVertex2f(0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(0.25, 0.5);
			glVertex2f(-0.25, 0.5);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.5);
			glVertex2f(-0.25, 0.25);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.25);
			glVertex2f(0.25, 0.25);
		}
		glEnd();
	}
	glPopMatrix();
}

void draw_negative()
{
	glPushMatrix();
	{
		glBegin(GL_LINES);
		{
			glVertex2f(-0.25, 0.25);
			glVertex2f(0.25, 0.25);
		}
		glEnd();
	}
	glPopMatrix();
}

void draw_single_digit(int x)
{
	switch (x)
	{
	case 0:
		draw_zero();
		break;
	case 1:
		draw_one();
		break;
	case 2:
		draw_two();
		break;
	case 3:
		draw_three();
		break;
	case 4:
		draw_four();
		break;
	case 5:
		draw_five();
		break;
	case 6:
		draw_six();
		break;
	case 7:
		draw_seven();
		break;
	case 8:
		draw_eight();
		break;
	case 9:
		draw_nine();
		break;
	case -1:
		draw_negative();
		break;
	default:
		break;
	}
	return;
}

void draw_speed_text(int speed)
{
	int x;
	int y;
	int z;
	int originalSpeed = speed;

	if (speed < 0)
	{
		speed *= -1;
	}

	glPushMatrix();
	{
		
		if (speed < 10)
		{
			x = speed;
			draw_single_digit(x);
			if (originalSpeed < 0)
			{
				glTranslatef(-0.6,0,0);
				draw_single_digit(-1);
			}
		}
		else if (speed < 100)
		{
			x = speed % 10;
			speed /= 10;
			y = speed % 10;
			draw_single_digit(x);
			glTranslatef(-0.6,0,0);
			draw_single_digit(y);
			if (originalSpeed < 0)
			{
				glTranslatef(-0.6,0,0);
				draw_single_digit(-1);
			}
		}
		else
		{
			x = speed % 10;
			speed /= 10;
			y = speed % 10;
			speed /= 10;
			z = speed % 10;
			draw_single_digit(x);
			glTranslatef(-0.6,0,0);
			draw_single_digit(y);
			glTranslatef(-0.6,0,0);
			draw_single_digit(z);
			if (originalSpeed < 0)
			{
				glTranslatef(-0.6,0,0);
				draw_single_digit(-1);
			}
		}
	}
	glPopMatrix();
}

void User_Interface::set_window_parameters(int height, int width) 
{
	this->window_height = height;
	this->window_width = width;
}



void User_Interface::reticular_translate(int x, int y)
{
	float tx;
	float ty;

	x -= this->window_width/2;
	y -= this->window_height/2;

	tx = x/150.0;
	ty = y/150.0;

	if( tx*tx + ty*ty <= 36)
	{
		glTranslatef(tx, -ty, 0);
	}
}

void User_Interface::draw_interface(float velocity_mag, int mousex, int mousey, GLfloat roll)
{
	if (velocity_mag < 0.0 && old_mag != velocity_mag)
	{
		if (old_mag > velocity_mag)
		{
			shipBackwardSpeed += 1;
			shipForwardSpeed -= 1;
		}
		else
		{
			shipBackwardSpeed -= 1;
			shipForwardSpeed += 1;
		}
		old_mag = velocity_mag;		
	}
	else if (velocity_mag > 0.0 && old_mag != velocity_mag)
	{
		if (old_mag < velocity_mag)
		{
			shipBackwardSpeed -= 1;
			shipForwardSpeed += 1;
		}
		else
		{
			shipBackwardSpeed += 1;
			shipForwardSpeed -= 1;
		}
		old_mag = velocity_mag;
	}
	else if ( velocity_mag == 0)
	{
		old_mag = velocity_mag;
		shipBackwardSpeed = 0;
		shipForwardSpeed = 0;
	}

	float i;
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	/* Hud */
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();      
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	// Set Color
	set_color();

	// Center Recticular
	
	glPushMatrix();
	{
		reticular_translate(mousex, mousey);
		drawHollowCircle(0,0,0.2);
		glBegin(GL_LINES);
		{
			glVertex2f(0.2, 0.0);
			glVertex2f(0.6, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-0.2, 0.0);
			glVertex2f(-0.6, 0.0);
		}
		glEnd();
	}
	glPopMatrix();	

	// Yaw Display
	for (i = 0; i < 360; i += 22.5)
	{
		glPushMatrix();
		{
			glRotatef(i, 0,0,1);
			glBegin(GL_LINES);
			{
				glVertex2f(5.0, 0.0);
				glVertex2f(6.0, 0.0);
			}
			glEnd();
		}
		glPopMatrix();
	}

	// Yaw Pointers
	glPushMatrix();
	{
		glRotatef(roll*180/3.14159265359, 0, 0, 1);

		// Right Pointer
		glBegin(GL_LINES);
		{
			glVertex2f(4.0, 0.0);
			glVertex2f(4.5, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(4.0, 0.0);
			glVertex2f(4.25, 0.25);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(4.5, 0.0);
			glVertex2f(4.25, 0.25);
		}
		glEnd();

		// Left Pointer
		glBegin(GL_LINES);
		{
			glVertex2f(-4.0, 0.0);
			glVertex2f(-4.5, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-4.0, 0.0);
			glVertex2f(-4.25, 0.25);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-4.5, 0.0);
			glVertex2f(-4.25, 0.25);
		}
		glEnd();
	}
	glPopMatrix();


	// Forward Speed Display
	drawHollowSemiCircle(0, 0, 6.5, 135, 225);
	drawHollowSemiCircle(0, 0, 7.0, 135, 225);
	glPushMatrix();
	{
		glRotatef(135, 0,0,1);
		glBegin(GL_LINES);
		{
			glVertex2f(6.5, 0.0);
			glVertex2f(7.0, 0.0);
		}
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glRotatef(225, 0,0,1);
		glBegin(GL_LINES);
		{
			glVertex2f(6.5, 0.0);
			glVertex2f(7.0, 0.0);
		}
		glEnd();
	}
	glPopMatrix();


	// Backward Speed Display
	drawHollowSemiCircle(0, 0, 6.5, 315, 45);
	drawHollowSemiCircle(0, 0, 7.0, 315, 45);
	glPushMatrix();
	{
		glRotatef(45, 0,0,1);
		glBegin(GL_LINES);
		{
			glVertex2f(6.5, 0.0);
			glVertex2f(7.0, 0.0);
		}
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glRotatef(-45, 0,0,1);
		glBegin(GL_LINES);
		{
			glVertex2f(6.5, 0.0);
			glVertex2f(7.0, 0.0);
		}
		glEnd();
	}
	glPopMatrix();

	// Speed Gage Zero Line
	if (shipForwardSpeed == shipBackwardSpeed)
	{
		glBegin(GL_LINES);
		{
			glVertex2f(6.5, 0.0);
			glVertex2f(7.0, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-6.5, 0.0);
			glVertex2f(-7.0, 0.0);
		}
		glEnd();
	}

	// Backward Speed
	if (shipBackwardSpeed >= 400)
	{
		drawSpeedGage_Backward(0, 0, 135.0, 157.5);
		drawSpeedGage_Backward(0, 0, 157.5, 180.0);
		drawSpeedGage_Backward(0, 0, 180.0, 202.5);
		drawSpeedGage_Backward(0, 0, 202.5, 225.0);
	}
	else if (shipBackwardSpeed >= 0 && shipBackwardSpeed <= 400)
	{
		if (shipBackwardSpeed <= 100)
		{
			drawSpeedGage_Backward(0, 0, 135.0, shipBackwardSpeed*0.225+135.0);
		}
		else if (shipBackwardSpeed <= 200)
		{
			drawSpeedGage_Backward(0, 0, 135.0, 157.5);
			drawSpeedGage_Backward(0, 0, 157.5, shipBackwardSpeed*0.225+135.0);
		}
		else if (shipBackwardSpeed <= 300)
		{
			drawSpeedGage_Backward(0, 0, 135.0, 157.5);
			drawSpeedGage_Backward(0, 0, 157.5, 180.0);
			drawSpeedGage_Backward(0, 0, 180.0, shipBackwardSpeed*0.225+135.0);
		}
		else
		{
			drawSpeedGage_Backward(0, 0, 135.0, 157.5);
			drawSpeedGage_Backward(0, 0, 157.5, 180.0);
			drawSpeedGage_Backward(0, 0, 180.0, 202.5);
			drawSpeedGage_Backward(0, 0, 202.5, shipBackwardSpeed*0.225+135.0);
		}
	}

	// Forward Speed
	if (shipForwardSpeed >= 400)
	{
		drawSpeedGage_Backward(0, 0, -45.0, -22.5);
		drawSpeedGage_Backward(0, 0, -22.5, 0.0);
		drawSpeedGage_Backward(0, 0, 0.0, 22.5);
		drawSpeedGage_Backward(0, 0, 22.5, 45.0);
	}
	else if (shipForwardSpeed >= 0 && shipForwardSpeed <= 400)
	{
		if (shipForwardSpeed <= 100)
		{
			drawSpeedGage_Backward(0, 0, -45.0, shipForwardSpeed*0.225-45.0);
		}
		else if (shipForwardSpeed <= 200)
		{
			drawSpeedGage_Backward(0, 0, -45.0, -22.5);
			drawSpeedGage_Backward(0, 0, -22.5, shipForwardSpeed*0.225-45.0);
		}
		else if (shipForwardSpeed <= 300)
		{
			drawSpeedGage_Backward(0, 0, -45.0, -22.5);
			drawSpeedGage_Backward(0, 0, -22.5, 0.0);
			drawSpeedGage_Backward(0, 0, 0.0, shipForwardSpeed*0.225-45.0);
		}
		else
		{
			drawSpeedGage_Backward(0, 0, -45.0, -22.5);
			drawSpeedGage_Backward(0, 0, -22.5, 0.0);
			drawSpeedGage_Backward(0, 0, 0.0, 22.5);
			drawSpeedGage_Backward(0, 0, 22.5, shipForwardSpeed*0.225-45.0);
		}
	}

	// Draw Forward Speed Text
	glPushMatrix();
	{
		glTranslatef(6.0,-6.0,0.0);
		draw_speed_text(shipForwardSpeed);
	}
	glPopMatrix();

	// Draw Backward Speed Text
	glPushMatrix();
	{
		glTranslatef(-6.0,-6.0,0.0);
		draw_speed_text(shipBackwardSpeed);
	}
	glPopMatrix();

	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();
	glPopAttrib();

	// END HUD
}