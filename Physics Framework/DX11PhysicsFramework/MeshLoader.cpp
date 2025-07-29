#include "MeshLoader.h"

namespace MeshLoader
{
	std::vector<Vector3> LoadObj(char* path)
	{
		ifstream t_InFile;
		t_InFile.open(path);

		if (!t_InFile.good()) 
		{ 
			std::cerr << "Can not open OBJ file: " << path << endl;
			std::vector<Vector3> t_Vertices;
			return t_Vertices;
		}

		return LoadObjVertices(t_InFile, path);
	}

	std::vector<Vector3> LoadObjVertices(ifstream& InFile, char* path)
	{
		std::vector<Vector3> t_Vertices;

		// File Variables
		std::string MeshReadData{};
		std::ifstream MaterialInFile;
		std::string MaterialReadData{};

		// Counting Contents Variables
		unsigned int VerticesCount{};
		unsigned int VertexNormalCount{};
		unsigned int VertexTextureCount{};
		unsigned int FCount{};

		// Vertex
		Vector3 Pos = Vector3();

		std::vector < Vector3 > PositionArray;

		// Face Vertex
		Vector3 FVer;


		while (!InFile.eof())
		{
			if (InFile.eof())
				break;

			std::getline(InFile, MeshReadData);

			if (MeshReadData[0] == 'v' && MeshReadData[1] == ' ')
			{
				++VerticesCount;
				sscanf_s(MeshReadData.c_str(), "v %f %f %f", &Pos.x, &Pos.y, &Pos.z);
				PositionArray.push_back(Pos);
			}
		}

		t_Vertices.insert(t_Vertices.end(), PositionArray.begin(), PositionArray.end());
		return t_Vertices;
	}
};