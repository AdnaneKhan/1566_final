#include "User_Interface.hpp"

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

void User_Interface::draw_interface(float velocity_mag)
{

	int shipForwardSpeed = (int)velocity_mag * 4;
	int shipBackwardSpeed = (int)velocity_mag * -4;

	float i;
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);

	/* Hud */
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();        ----Not sure if I need this
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	// Center Recticular
	glColor3f(1.0f, 0.0f, 0.0f);
	drawHollowCircle(0,0,0.2);
	glPushMatrix();
	{
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
		glBegin(GL_LINES);
		{
			glVertex2f(4.0, 0.0);
			glVertex2f(4.5, 0.0);
		}
		glEnd();
		glBegin(GL_LINES);
		{
			glVertex2f(-4.0, 0.0);
			glVertex2f(-4.5, 0.0);
		}
		glEnd();
	}
	glPopMatrix();


	// Forward Speed Display
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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

	// Speed Gage
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

	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glPopAttrib();

	// END HUD
}