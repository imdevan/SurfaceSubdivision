#include "ObjectSubdivider.h"
#include <algorithm>    // std::min

int SubDivider::jminus1(int j){
	if (j == 0) return 3;
	else return j - 1;
}
Vertex SubDivider::getVert(Object & obj, vector<Vertex> & newV, int i1, int i2, bool & foundInHash){
	int a = min(i1, i2);
	int b = max(i2, i1);
	pair<int, int> vertexKey = make_pair(a, b);
		
	// if orderless key(i1, i2) not in hash
	if (hash.count(vertexKey) == 0){

		Vertex v1 = obj.vertexVector[vertexKey.first - 1];
		Vertex v2 = obj.vertexVector[vertexKey.second -1];
		Vertex midpoint;

		// add midpoint ofo V[i1], V[i2] to newV
		midpoint = Vertex(
			(v2.x() + v1.x()) / (float)2.0,
			(v2.y() + v1.y()) / (float)2.0,
			(v2.z() + v1.z()) / (float)2.0
			);

		newV.push_back(midpoint);

		midpoint.index = newV.size();

		// hash[(i1, i2)] = index of new point
		hash.insert(make_pair(vertexKey, midpoint));
	}
	else foundInHash = true;

	// return hash[(i1,i2)]
	return hash.at(vertexKey);
}

Vertex SubDivider::getCentroid(Object & obj, Face f){
	float x = (obj.vertexVector[f.v[0] - 1].x() + 
			   obj.vertexVector[f.v[1] - 1].x() + 
			   obj.vertexVector[f.v[2] - 1].x() + 
			   obj.vertexVector[f.v[3] - 1].x()
			   ) / 4.0;
	float y = (obj.vertexVector[f.v[0] - 1].y() + 
			   obj.vertexVector[f.v[1] - 1].y() + 
			   obj.vertexVector[f.v[2] - 1].y() + 
			   obj.vertexVector[f.v[3] - 1].y()
			   ) / 4.0;
	float z = (obj.vertexVector[f.v[0] - 1].z() + 
			   obj.vertexVector[f.v[1] - 1].z() + 
			   obj.vertexVector[f.v[2] - 1].z() + 
			   obj.vertexVector[f.v[3] - 1].z()
			   ) / 4.0;

	return Vertex(x, y, z);
}

void SubDivider::clearHash(){
	hash.clear();
}

void SubDivider::linearSub(Object & obj){
	vector<Face> of = obj.faceVector;
	vector<Vertex> newV = obj.vertexVector;
	vector<Face> newF = vector<Face>();
	vector<pair<int, Vertex>> e;
	pair<int, Vertex> c;
	hash.clear();

	// for each face
	for (int fi = 0; fi < of.size(); fi++){
		e.clear();
		// for j = 1 to 4
		for (int j = 0; j < 4; j++){

			// calculate midpoint vertex and add it to newV
			bool foundInHash = false;
			Vertex midEdgeVertex = getVert(obj, newV, of[fi].v[j], of[fi].v[(j + 1) % 4], foundInHash);
			if (!foundInHash){

				// store the new vertex and its index in e
				e.push_back(
					make_pair(newV.size(), newV.back())
					);
			}
			else{
				e.push_back(make_pair(midEdgeVertex.index, newV.at(midEdgeVertex.index)));
			}
		}

		// add centroid to newV and store index in c
		newV.push_back(
			getCentroid(obj, of[fi])
		);
		c = make_pair(newV.size(), newV.back());

		// for j = 1 to 4
		for (int j = 0; j < 4; j++){
			// add face(Fij, ej, c, ej-1) to newF
			newF.push_back(
				Face(
					of[fi].v[j],
					e[j].first,
					c.first,
					e[jminus1(j)].first
				)
			);
		}
	}

	obj.faceVector = newF;
	obj.vertexVector = newV;
	obj.calculateNormals();
}

void SubDivider::average(Object & obj){
	vector<Vertex> newV = vector<Vertex>();
	vector<Vertex> ov = obj.vertexVector;
	vector<float> val = vector<float>();
	vector<Face> of = obj.faceVector;

	// val = array of 0
	// newV = 0 * V
	for (int i = 0; i < ov.size(); i++){
		val.push_back(0.0);
		newV.push_back(Vertex(0.0f, 0.0f, 0.0f));
	}

	// for each face
	for (int fi = 0; fi < of.size(); fi++){

		//getCentroid(obj, of[fi]);
		Vertex cent = getCentroid(obj, of[fi]);

		// newV[Fi] += cent
		for (int vi = 0; vi < 4; vi++){
			// find the ovbject vertex from face vertex
			int ovi = of[fi].v[vi] - 1;

			// Add centroid to the newV at ovi
			newV[ovi].coor[0] += cent.coor[0];
			newV[ovi].coor[1] += cent.coor[1];
			newV[ovi].coor[2] += cent.coor[2];

			// val[Fi] += 1
			val[ovi] += 1.0;
		}
	}

	// for each vertex newV[i]
	for (int vi = 0; vi < newV.size(); vi++){
		// newV[i] /= val[i]
		newV[vi].coor[0] /= (float)val[vi];
		newV[vi].coor[1] /= (float)val[vi];
		newV[vi].coor[2] /= (float)val[vi];
	}

	// return (newF, newV)
	//obj.faceVector = newF;
	obj.vertexVector = newV;
	obj.calculateNormals();
}

void SubDivider::subdivideObject(Object & obj){
	// linear subdivide
	linearSub(obj);
	// average
	average(obj);
}