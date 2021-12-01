#pragma once
class Terrain : public Renderer
{
public:
	Terrain(Shader* shader, wstring heigtmap);
	~Terrain();

public:
	typedef VertexTextureNormal TerrainVertex;

private:
	//Shader* shader;
	Texture*  heightMap;
	UINT width, height;

	//UINT vertexCount;
	TerrainVertex* vertices;
	//ID3D11Buffer* vertexBuffer;
	//VertexBuffer* vertexBuffer;

	//UINT indexCount;
	UINT* indices;
	//ID3D11Buffer* indexBuffer;
	//IndexBuffer* indexBuffer;

	//UINT pass;

	//Matrix world;

private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateNormalData();
	void CreateBuffer();

public:
	void Update();
	void Render();
	void BaseMap(wstring file);
	float GetHeight(Vector3 position);
	float GetPickedHeight(Vector3& position);
	Vector3 GetPosition();


	float GetPickedHeight();
	Vector3 GetPickedPosition();

};

