/* 
	Assignment 6: Subdivision Surfaces
    The purpose of this assignment is to implement a variation on Catmull-Clark subdivision surfaces.

	Project components:
	
		The project will be implemented by reading in obj files containing quardratic polygons.
		Objects should be lit by at least one light.
			This means calculating normals of the faces (flat shading should be used)
		OpenGL to do all of the rendering and lighting as well as hidden surface removal.
		

		User Stories:
			
			When the users presses the '+' key the suraes swill subdific by performing linear subdicision on the shape and then averaging subdivision.
			If the user presses the 'L' key, the object polygons shoul linearly subdivide.
			If the user presses the 'A' key, the object polygons should average subdivide.
			
			'+' is a combination of 'L' + 'A'

			The users should be able to zoom by dragging the right mouse button 
				as well as rotate the shape (both horizontally and vvertically)

	Notes:

		The chapter "Lighting" in the Red Book ehlpful for setting up light parameters.
		p. 210 in the 7th edition.
	
 */

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Object.h"
#include "GlutInterface.h"
using namespace std;

int main(int argc, char** argv)
{


	Object obj = Object(argv[1]);
	// cout << obj;
	//scanConvert(argc, argv, obj);

	glutInterface(argc, argv, obj);

	string foo;
	cin >> foo;
	return 0;

}