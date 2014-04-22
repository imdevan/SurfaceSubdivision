#ifndef OBJECT
#define OBJECT

#include "Geometry.h"
#include <string>
#include <vector>

using namespace std;

class Object{
public:
	// Variables
	vector<Vertex> vertexVector;
	vector<Norm> normalVector;
	vector<Face> faceVector;

	// Methods
	void load(string pFile);
	vector<string> parse(string& s, char& c);
	Vertex getVertex(int i);
	Face getFace(int i);

	Object();
	Object(ifstream& fin);
	Object(const char* pString);
};

ostream& operator<<(ostream& os, const Object& obj);

#endif 