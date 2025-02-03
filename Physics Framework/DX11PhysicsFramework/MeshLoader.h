#ifndef MESH_LOADER_H

#include "Structures.h"
#include "Constants.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

namespace MeshLoader
{
	
	std::vector<Vector3> LoadObj(char* path);

	std::vector<Vector3> LoadObjVertices(ifstream& InFile, char* path);

};

#endif