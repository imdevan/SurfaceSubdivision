/*
	My 3d OpenGL Program
*/

#include <Windows.h>	// Standard Windows Header
#include <gl/gl.h>		// The GL Header File
#include <GL/glut.h>	// The GL Utility Toolkit (Glut) Header
#include "GlutInterface.h"

float rotation;	
Object object;

void InitGL(GLvoid)		
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(100.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display(void)
{
	// Clear the screen and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset the current modelview matrix.
	glLoadIdentity();

	glPushMatrix();

	// Move left 1.5 units and into the screen 6.0.
	glTranslatef(0.0f, 0.0f, -100.0f);

	// Rotate the triangle on the y and z axis
	glRotatef(rotation, 1.0f, 1.0f, 0.0f);


	// Draw each face in the object
	for (int fi = 0; fi < object.faceVector.size(); fi++){

		
		glBegin(GL_QUADS);

		for (int vi = 0; vi < 4; vi++){
			Vertex v = object.getVertex(fi, vi);

			glColor3f(1.0f, 0.0f, 0.0f);	// Red
			glVertex3f(
				v.x(),
				v.y(),
				v.z()
			);	
		}

		glEnd();
	}

	glLoadIdentity();
	glPopMatrix();

	// Increase the rotation variable for the triangle.
	rotation += 0.02f;	

	// Swap the buffers to not be left with a clear screen.
	glutSwapBuffers();
}

// Create the reshape function (the viewport)
void reshape(int width, int height)
{
	if (height == 0){
		height = 1;
	}

	// Reset the current viewport.
	glViewport(0, 0, width, height);

	// Set the projection matrix.
	glMatrixMode(GL_PROJECTION);

	// Reset the projection matrix.
	glLoadIdentity();

	// Calculate the aspect ratio of the window.
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	// Select the modelview matrix.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key){
	case 27:	// escape key
	case 'q':
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}
}

void arrow_keys(int a_keys, int x, int y)
{
	switch (a_keys){
	case GLUT_KEY_UP:
		glutFullScreen();
		break;
	case GLUT_KEY_DOWN:
		glutReshapeWindow(500, 500);
	default:
		break;
	}
}

void glutInterface(int argc, char** argv, Object & obj)
{
	object = obj;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("NeHe OpenGL Adaptation");
	InitGL();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutIdleFunc(display);
	glutMainLoop();
}