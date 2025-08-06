#ifndef MESH_LOADER_H
#define MESH_LOADER_H // MIGHT NEED TO REMOVE THIS

#include "Vector3.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace MeshLoader
{
	std::vector<Vector3> LoadObj(char* path);
	std::vector<Vector3> LoadObjVertices(ifstream& InFile, char* path);
};

#endif