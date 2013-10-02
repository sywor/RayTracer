#pragma once

#include <D3DX10.h>
#include <vector>
#include <string>

struct PNTVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 norm;
	D3DXVECTOR2 uv;
};

struct Face
{
	PNTVertex verts[3];
	D3DXVECTOR4 Colour;
};

class OBJLoader
{
public:
	OBJLoader(void);
	~OBJLoader(void);

	bool load(std::vector<Face>& _faces, std::string _filepath);
};

