#pragma once
class Terrain
{
public:
	Terrain(Shader* shader, wstring heigtmap);
	~Terrain();

public:
	typedef Vertex TerrainVertex;

private:
	Shader* shader;
	Texture*  heightMap;
	UINT width, height;

	UINT vertexCount;
	TerrainVertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	ID3D11Buffer* indexBuffer;

	UINT pass;


	void CreateVertexData();
	void CreateIndexData();
	void CreateNormalData();
	void CreateBuffer();

public:
	void Update();
	void Render();
};

