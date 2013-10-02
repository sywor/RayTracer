#include "OBJLoader.h"
#include "OBJLoader.h"

#include <fstream>

OBJLoader::OBJLoader(void)
{
}


OBJLoader::~OBJLoader(void)
{
}

bool OBJLoader::load(std::vector<Face>& _faces, std::string _filepath)
{
	FILE* file = fopen(_filepath.c_str(), "r");
	std::vector<D3DXVECTOR3> tVertices, tNormals;
	std::vector<D3DXVECTOR2> tUvs;
	std::vector<unsigned int> vIndices, nIndices, uvIndices;
	std::vector<PNTVertex> _vertices;

	if(file == NULL)
		return false;


	while(true)
	{
		char line[128];
		int res = fscanf(file,"%s",line);
		if(res == EOF)
			break;

		if(strcmp(line, "v") == 0)
		{
			D3DXVECTOR3 v;
			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);
			tVertices.push_back(v);
		}
		else if(strcmp(line, "vn") == 0)
		{
			D3DXVECTOR3 n;
			fscanf(file,"%f %f %f\n", &n.x,&n.y,&n.z);
			tNormals.push_back(n);
		}
		else if(strcmp(line, "vt") == 0)
		{
			D3DXVECTOR2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			tUvs.push_back(uv);
		}
		else if(strcmp(line, "f") == 0)
		{
			unsigned int vInd[3], nInd[3], uvInd[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vInd[0], &uvInd[0], &nInd[0],
														 &vInd[1], &uvInd[1], &nInd[1],
														  &vInd[2], &uvInd[2], &nInd[2]);

			if(matches != 9)
				return false;

			for(int i = 0; i < 3; i++)
			{
				vIndices.push_back(vInd[i]);
				uvIndices.push_back(uvInd[i]);
				nIndices.push_back(nInd[i]);
			}
		}


	}

	for(unsigned int i = 0; i < vIndices.size(); i++)
	{
		PNTVertex v;
		unsigned int vertexIndex = vIndices[i] - 1;
		unsigned int NormalIndex = nIndices[i] - 1;
		unsigned int uvIndex = uvIndices[i] - 1;

		v.pos = tVertices[vertexIndex];
		v.norm = tNormals[NormalIndex];
		v.uv = tUvs[uvIndex];

		_vertices.push_back(v);
	}

	for(unsigned int i = 0; i < _vertices.size(); i+=3)
	{
		PNTVertex v1, v2, v3;
		v1 = _vertices[i];
		v2 = _vertices[i+1];
		v3= _vertices[i+2];

		Face f;
		f.verts[0] = v1;
		f.verts[1] = v2;
		f.verts[2] = v3;
		f.Colour = D3DXVECTOR4(0.5f, 0.1f, 0.1f, 1.f);
		_faces.push_back(f);
	}

	return true;
}