#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(Shader * shader, wstring heightmap)
	: Render(shader)
	, BaseMap(NULL)
	, spacing(3, 3)
{
	this->heightMap = new Texture(heightmap);
	CreateVertexData();
	CreateIndexData();
	CreateNormalData();
	CreateBuffer();
	sBaseMap = shader->AsSRV("BaseMap");

	//D3DXMatrixIdentity(&world);
}

Terrain::~Terrain()
{
	SafeDelete(heightMap);

	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	//SafeDelete(vertexBuffer);
	//SafeDelete(indexBuffer);
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
			UINT pixel = width * (height)z + x;

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
	//
	/*for(UINT i = 0; i<vertexCount; i++)
		D3DXVec3Normalize(&vertices[i].Normal, &vertices[i].Normal)*/
}

void Terrain::CreateBuffer()
{
	vertexBuffer = new VertexBuffer(vertices, vertexCount, sizeof(TerrainVertex));
	indexBuffer = new IndexBuffer(indices, indexCount);
}

void Terrain::Update()
{
	__super::Update();
	//Matrix world;
	//D3DXMatrixIdentity(&world);
	//shader->AsMatrix("World")->SetMatrix(world);
	//shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	//shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void Terrain::Render()
{
	/*UINT stride = sizeof(TerrainVertex);
	UINT offset = 0;

	vertexBuffer->Render();
	indexBuffer->Render();

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);*/

	Super::Render();
	shader->DrawIndexed(0, Pass(), indexCount);
}

void Terrain::BaseMap(wstring file)
{
	//
	//SafeDelete(baseMap);
}

float Terrain::GetPickedHeight()
{
	return 0.0f;
}

Vector3 Terrain::GetPickedPosition()
{
	Vector3 start, direction;
	Matrix V = Context::Get()->View();
	Matrix P = Context::Get()->Projection();

	//Context::Get()->GetViewport()->GetRay(&start, &direction, world, V, P);

	Matrix world = GetTransform()->World();
	Vector3 mouse = Mouse::Get()->GetPosition();
	Vector3 n, f;
	mouse.z = 0.0f;
	Context::Get()->GetViewport()->Unproject(&m, mouse, world, V, P);

	mouse.z = 1.0f;
	Context::Get()->GetViewport()->Unproject(&f, mouse, world, V, P);
	
	direction = f - n;
	start = n;

	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width - 1; x++)
		{
			UINT index[4];
			//index[0] = width * ();
		}
	}

	float u, v, distance;
	// left down
	/*if (D3DXIntersectTri(&p[0], &p[1], &p[2], &start, &direction,
		&u, &v, &distance) == TRUE)
	return */

}
