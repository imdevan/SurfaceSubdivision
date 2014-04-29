#ifndef GEOMETRY
#define GEOMETRY
#include <iostream>
using namespace std;

#define ImageW 400
#define ImageH 400

struct Norm {
	float dir[3];

	float x();
	float y();
	float z();

	void normalize();
	Norm();
	Norm(int px, int py, int pz);
};

struct Vertex{

	float coor[3];
	Norm norm;
	float color[3];


	float x();
	float y();
	float z();

	void transformToWC();
	Vertex(float px, float py, float pz);
	Vertex();
	Vertex& operator+=(const Vertex& rhs);
};


struct Face{

	int v[4];

	// calculated imediately after the face has been added to an object.
	// Object.cpp - Object::load() - case 'f'
	Norm norm;


	void setNorm(Vertex v1, Vertex v2, Vertex v3, Vertex v4);
	Face(int pv1, int pv2, int pv3, int pv4);
	Face();
};

ostream& operator<<(ostream& os, const Vertex& vt);
ostream& operator<<(ostream& os, const Face& f);
ostream& operator<<(ostream& os, const Norm& n);
Norm operator+(const Norm& n1, const Norm& n2);
#endif 