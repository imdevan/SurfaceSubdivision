#include "Geometry.h"

// ======================================================================
// Vertex
// ======================================================================
Vertex::Vertex(float px, float py, float pz) :
coor(), norm(), color() {
	coor[0] = px;
	coor[1] = py;
	coor[2] = pz;
}
Vertex::Vertex() :
coor(), norm(), color() {}
void Vertex::transformToWC(){

	float x = coor[0];
	float y = coor[1];
	float sw = (ImageW - 1) / 2;
	float sh1 = (1 - ImageH) / 2;
	float sh2 = (ImageH - 1) / 2;
	float m[3][3] = {
		{ sw, 0, sw },
		{ 0, sh1, sh2 },
		{ 0, 0, 1 }
	};

	coor[0] = m[0][0] * x + m[0][1] * y + m[0][2] * 1;
	coor[1] = m[1][0] * x + m[1][1] * y + m[1][2] * 1;

}
float Vertex::x(){ return coor[0]; }
float Vertex::y(){ return coor[1]; }
float Vertex::z(){ return coor[2]; }
ostream& operator<<(ostream& os, const Vertex& vt)
{
	os << vt.coor[0] << " " << vt.coor[1] << " " << vt.coor[2] << "\n";
	return os;
}

// ======================================================================
// Face
// ======================================================================
Face::Face(int pv1, int pv2, int pv3, int pv4) :
v() {
	v[0] = pv1;
	v[1] = pv2;
	v[2] = pv3;
	v[3] = pv4;
}
Face::Face() :
v() {}
void Face::setNorm(Vertex v1, Vertex v2, Vertex v3, Vertex v4){
	// calculate the vectors
	Vertex _v1 = Vertex(v3.x() - v1.x(), v3.y() - v1.y(), v3.z() - v1.z());
	Vertex _v2 = Vertex(v4.x() - v2.x(), v4.y() - v2.y(), v4.z() - v2.z());

	// cross multiply vectors to derive normal
	norm.dir[0] = (_v1.y() * _v2.z()) - (_v1.z() * _v2.y());
	norm.dir[1] = -((_v2.z() * _v1.x()) - (_v2.x() * _v1.z()));
	norm.dir[2] = (_v1.x() * _v2.y()) - (_v1.y() * _v2.x());
	norm.normalize();
}	
ostream& operator<<(ostream& os, const Face& f)
{
	os << f.v[0] << " " << f.v[1] << " " << f.v[2] << " " << f.v[3] << "\n";
	return os;
}

// ======================================================================
// Norm
// ======================================================================
Norm::Norm() : dir() {}
Norm::Norm(int px, int py, int pz) : dir()
{
	dir[0] = px;
	dir[1] = py;
	dir[2] = pz;
}
void Norm::normalize(){
	float mag = sqrt(pow(dir[0], 2) + pow(dir[1], 2) + pow(dir[2], 2));
	dir[0] = dir[0] / mag;
	dir[1] = dir[1] / mag;
	dir[2] = dir[2] / mag;
}
float Norm::x(){ return dir[0]; }
float Norm::y(){ return dir[1]; }
float Norm::z(){ return dir[2]; }
ostream& operator<<(ostream& os, const Norm& n)
{
	os << "n: " << n.dir[0] << " " << n.dir[1] << " " << n.dir[2] << "\n";
	return os;
}
Norm operator+(Norm &n1, const Norm &n2)
{
	// use the Norm constructor and operator+(int, int)
	return Norm(
		n1.dir[0] + n2.dir[0],
		n1.dir[1] + n2.dir[1],
		n1.dir[2] + n2.dir[2]
		);
}