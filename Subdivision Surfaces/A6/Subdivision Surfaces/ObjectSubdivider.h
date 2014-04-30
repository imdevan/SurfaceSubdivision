#ifndef OBJECT_SUBDIVIDER
#define OBJECT_SUBDIVIDER

#include <map>
#include "Object.h"
#include <hash_map>

using namespace stdext;





typedef pair<int, int> VertexKey;

class SubDivider{
public:
	void linearSub(Object & obj);
	void average(Object & obj);
	void subdivideObject(Object & obj);

private:



	// hashes midpoints that have already been created
	map<VertexKey, Vertex> hash;

	// Creates a midpoint from and object and the index of two vertices.
	// Indicies derived from faces; must subtract one in function.
	Vertex getVert(Object & obj, vector<Vertex> & newV, int i1, int i2, bool & foundInHash);


	// clears the hash
	void clearHash();

	// returns 3 if j - 1 = -1
	int jminus1(int j);

	// Averages the vertices of a face
	Vertex getCentroid(Object & obj, Face f);
};




#endif