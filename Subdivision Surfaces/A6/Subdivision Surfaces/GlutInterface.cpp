/*
	My 3d OpenGL Program
*/

#include <Windows.h>	// Standard Windows Header
#include <gl/gl.h>		// The GL Header File
#include <gl/glut.h>	// The GL Utility Toolkit (Glut) Header
#include "GlutInterface.h"

float rotation;	
Object object;
SubDivider objSubDivider;
int downX, downY;
float phi = 0, theta = 0;
float sdepth = 5;
bool leftButton = false, rightButton = false, showWireFrame = false;

void InitGL(GLvoid)		
{
	glShadeModel(GL_FLAT);
	glClearColor(247 / 255.0f, 228 / 255.0f, 190 / 255.0f, 0.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHT1); 
	glEnable(GL_COLOR_MATERIAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
// 247,228,190
void display(void)
{
    // Show wire frame.
	if (showWireFrame) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Clear the screen and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset the current modelview matrix.
	glLoadIdentity();

	//Add positioned light
	GLfloat lightColor0[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	GLfloat lightPos0[] = { -1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = { -1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glPushMatrix();

	// Move left 1.5 units and into the screen 6.0.
	glTranslatef(0.0, 0.0, -sdepth);
	glRotatef(-theta, 1.0, 0.0, 0.0);
	glRotatef(-phi, 0.0, 1.0, 0.0);


	// Rotate the object on the y and z axis
	// glRotatef(rotation, 1.0f, 1.0f, 0.0f);


	// Draw each face in the object
	for (int fi = 0; fi < object.faceVector.size(); fi++){

		
		glBegin(GL_QUADS);

		for (int vi = 0; vi < 4; vi++){
			Vertex v = object.getVertex(fi, vi);
			Norm n = object.faceVector[fi].norm;

			glNormal3f(
				n.x(),
				n.y(),
				n.z()
			);
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
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100000.0f);

	// Select the modelview matrix.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
	downX = x; downY = y;
	leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
	rightButton = ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN));
	glutPostRedisplay();
}

void motion(int x, int y) 
{
	// rotate
	if (leftButton){ 
		phi -= (float)(x - downX) / 2.0; 
		theta += (float)(downY - y) / 2.0; 
	}

	// scale
	if (rightButton){ 
		sdepth -= (float)(downY - y) / 5.0; 
	} 

	downX = x;   downY = y;
	glutPostRedisplay();
}	

void keyboard(unsigned char key, int x, int y)
{
	switch (key){
	case 27:	// escape key
	case 'q':
	case 'Q':
		exit(0);
		break;
	case 'l':
	case'L':
		objSubDivider.linearSub(object);
		break;
	case 'a':
	case'A':
		objSubDivider.average(object);
		break;
	case 'W':
	case'w':
		if (showWireFrame)
			showWireFrame = false;
		else
			showWireFrame = true;
		break;
	case'+':
	case'=':
		objSubDivider.subdivideObject(object);
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
		break;
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
	glutCreateWindow("Devan Huapaya - Assignment 6");
	InitGL();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutIdleFunc(display);
	glutMainLoop();
}