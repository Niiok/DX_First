#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(Shader * shader, wstring heightmap)
	:shader(shader), pass(0)
{
	this->heightMap = new Texture(heightmap);
	CreateVertexData();
	CreateIndexData();
	CreateBuffer();
}

Terrain::~Terrain()
{
	SafeDelete(heightMap);

	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void Terrain::CreateVertexData()
{
	vector< Color > heights;
	heightMap->ReadPixels(DXGI_FORMAT_R8G8B8A8_UNORM, &heights);

	width = heightMap->GetWidth();
	height = heightMap->GetHeight();

	vertexCount = width * height;
	vertices = new TerrainVertex[vertexCount];

	for (UINT z = 0; z < height; z++)
	{
		for(UINT x = 0; x < width; x++)
		{
			UINT index = width * z + x;

			vertices[index].Position.y = heights[index];
		}
	}
}

void Terrain::CreateIndexData()
{
	indexCount = (width - 1)* (height - 1) * 6;
	indices = new UINT[indexCount];

	UINT index = 0;
	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width - 1; x++)
		{
			indices[index + 0] = width * (z + 0) + (x + 0);
			indices[index + 1] = width * (z + 1) + (x + 0);
			indices[index + 2] = width * (z + 0) + (x + 1);

			indices[index + 3] = width * (z + 0) + (x + 1);
			indices[index + 4] = width * (z + 1) + (x + 0);
			indices[index + 5] = width * (z + 1) + (x + 1);

			index += 6;
		}
	}
}

void Terrain::CreateNormalData()
{

}

void Terrain::CreateBuffer()
{
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	}

	{

	}
}

void Terrain::Update()
{
	Matrix world;
	D3DXMatrixIdentity(&world);
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void Terrain::Render()
{
	UINT stride = sizeof(TerrainVertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer()


}
