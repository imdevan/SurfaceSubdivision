#include "Object.h"
#include <fstream>
#include <iostream>

Object::Object() : vertexVector(), faceVector(), normalVector() {}
Object::Object(const char* pString) : vertexVector(), faceVector(), normalVector() {
	load(pString);
}
ostream& operator<<(ostream& os, const Object& obj)
{
	os << "Verticies: \n";
	for (unsigned int i = 0; i < obj.vertexVector.size(); i++){
		os << obj.vertexVector.at(i);
	}
	os << "\n\nFaces: \n";
	for (unsigned int i = 0; i < obj.faceVector.size(); i++){
		os << obj.faceVector.at(i);
	}
	os << "\n";

	return os;
}
Vertex Object::getVertex(int fi, int vi){
	return vertexVector[faceVector[fi].v[vi] - 1];
}
vector<string> Object::parse(string& s, char& c){
	vector<string> rVector;
	string temp = "";

	for (unsigned int i = 0; i < s.length(); i++){
		if (s[i] == c){
			rVector.push_back(temp);
			temp.clear();
		}
		else {
			temp += s[i];
		}
	}
	rVector.push_back(temp);// end of line
	return rVector;
}
void Object::calculateNormals(){
	for (int fi = 0; fi < faceVector.size(); fi++)
		faceVector[fi].setNorm(
			vertexVector[faceVector[fi].v[0] - 1],
			vertexVector[faceVector[fi].v[1] - 1],
			vertexVector[faceVector[fi].v[2] - 1],
			vertexVector[faceVector[fi].v[3] - 1]
		);
		
}
void Object::load(string pFile){
	ifstream the_file;

	the_file.open(pFile);

	if (the_file.is_open() == false)
		cout << "Could not open file ";
	else {
		string line;
		char c = ' ';
		vector<string> lineVector;
		// returns false if the end of the file
		//  is reached or an error occurs
		while (getline(the_file, line)){
			switch (line[0])
			{
			case 'v':
				lineVector = parse(line, c);
				/*for (unsigned int i = 0; i < lineVector.size(); i++)
				cout << lineVector.at(i);*/
				vertexVector.push_back(
					Vertex(
						stof(lineVector.at(1)),
						stof(lineVector.at(2)),
						stof(lineVector.at(3))	
					)
				);
				break;
			case'f':
				lineVector = parse(line, c);

				// if their were two spaces after 'f':
				if (lineVector.at(1) == "")
						faceVector.push_back(
							Face(
							stoi(lineVector.at(2)),
							stoi(lineVector.at(3)),
							stoi(lineVector.at(4)),
							stoi(lineVector.at(5))
							)
						);
				else
					faceVector.push_back(
						Face(
							stoi(lineVector.at(1)),
							stoi(lineVector.at(2)),
							stoi(lineVector.at(3)),
							stoi(lineVector.at(4))
						)
					);
				// calc norm of face after adding
				faceVector.back().setNorm(
					vertexVector.at(faceVector.back().v[0] - 1),
					vertexVector.at(faceVector.back().v[1] - 1),
					vertexVector.at(faceVector.back().v[2] - 1),
					vertexVector.at(faceVector.back().v[3] - 1)
				);


				break;
			default:
				break;
			}
		}
	}
}
