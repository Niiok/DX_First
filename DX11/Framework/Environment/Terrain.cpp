#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(Shader * shader, wstring heightmap)
	//: shader(shader)
	//, pass(1)
	: Renderer(shader)
	, baseMap(NULL)
	, layerMap(NULL)
	, alphaMap(NULL)
	, spacing(3, 3)
{
	this->heightMap = new Texture(heightmap);
	CreateVertexData();
	CreateIndexData();
	CreateNormalData();
	CreateBuffer();
	sBaseMap = shader->AsSRV("BaseMap");
	sLayerMap = shader->AsSRV("LayerMap");
	sAlphaMap = shader->AsSRV("AlphaMap");

	//D3DXMatrixIdentity(&world);

	brushBuffer = new ConstantBuffer(&brushDesc, sizeof(BrushDesc));
	sBrushBuffer = shader->AsConstantBuffer("CB_TerrainBrush");

	lineColorBuffer = new ConstantBuffer(&lineColorDesc, sizeof(LineColorDesc));
	sLineColorBuffer = shader->AsConstantBuffer("CB_GridLine");
}

Terrain::~Terrain()
{
	SafeDelete(heightMap);
	SafeDelete(brushBuffer);

	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	//SafeDelete(vertexBuffer);
	//SafeDelete(indexBuffer);
}

void Terrain::CreateVertexData()
{
	vector< Color > heights;
	heightMap->ReadPixel(DXGI_FORMAT_R8G8B8A8_UNORM, &heights);

	width = heightMap->GetWidth();
	height = heightMap->GetHeight();

	{
		FILE* file = fopen("test.csv", "w");
		for (UINT y = 0; y < height; y++)
		{
			for (UINT x = 0; x < width; x++)
			{
				UINT index = width * y + x;
				UINT r = (UINT)(heights[index].r * 255);
				UINT g = (UINT)(heights[index].g * 255);
				UINT b = (UINT)(heights[index].b * 255);
				UINT a = (UINT)(heights[index].a * 255);
				fprintf(file, "%d, %d, %d, %d, %d, %d, %d",
					index, x, y, (UINT)r, (UINT)g, (UINT)b, (UINT)a);
			}
		}
		fclose(file);
	}

	vertexCount = width * height;
	vertices = new TerrainVertex[vertexCount];

	for (UINT z = 0; z < height; z++)
	{
		for(UINT x = 0; x < width; x++)
		{
			UINT index = width * z + x;
			UINT pixel = width * (height - 1 -z) + x;

			vertices[index].Position.x = (float)x;
			//vertices[index].Position.y = heights[index].r * 255.0f / 10.0f;
			vertices[index].Position.y = heights[pixel].r * 255.0f / 10.0f;
			vertices[index].Position.z = (float)z;

			vertices[index].Uv.x = ((float)x / (float)width) /** spacing.x*/;
			vertices[index].Uv.y = ((float)(height - 1 - z) / (float)height) /** spacing.y*/;
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
	for (UINT i = 0; i < indexCount / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		TerrainVertex v0 = vertices[index0];
		TerrainVertex v1 = vertices[index1];
		TerrainVertex v2 = vertices[index2];

		Vector3 d1 = v1.Position - v0.Position;
		Vector3 d2 = v2.Position - v0.Position;

		Vector3 normal;
		D3DXVec3Cross(&normal, &d1, &d2);

		vertices[index0].Normal += normal;
		vertices[index1].Normal += normal;
		vertices[index2].Normal += normal;
	}


	for (UINT i = 0; i < vertexCount; i++)
	{
		D3DXVec3Normalize(&vertices[i].Normal, &vertices[i].Normal);
	}
}

void Terrain::CreateBuffer()
{
	vertexBuffer = new VertexBuffer(vertices, vertexCount, sizeof(TerrainVertex)
	, 0, false, true);
	indexBuffer = new IndexBuffer(indices, indexCount);
}

void Terrain::Update()
{
	Super::Update();
	//Matrix world;
	//D3DXMatrixIdentity(&world);
	//shader->AsMatrix("World")->SetMatrix(world);
	//shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	//shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());

	ImGui::InputInt("Brush Type", (int*)&brushDesc.Type);
	brushDesc.Type %= 3;

	ImGui::ColorEdit3("Brush Color", (float*)&brushDesc.Color);
	ImGui::InputInt("Brush Range", (int*)&brushDesc.Range);
	
	ImGui::Separator();
	ImGui::ColorEdit3("Line Color", (float*)&lineColorDesc.Color);
	ImGui::InputFloat("Thickness", &lineColorDesc.Thickness);
	ImGui::InputFloat("Size", &lineColorDesc.Size, 1.0f);


	if (brushDesc.Type > 0) 
	{
		Vector3 position = GetPickedPosition();
		brushDesc.Location = position;

		if (Mouse::Get()->Press(0))
		{
			RaiseHeight(position, brushDesc.Type, brushDesc.Range);
		}
	}
}

void Terrain::Render()
{
	/*UINT stride = sizeof(TerrainVertex);
	UINT offset = 0;

	vertexBuffer->Render();
	indexBuffer->Render();

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);*/

	Super::Render();

	if (sBrushBuffer != NULL)
	{
		brushBuffer->Apply();
		sBrushBuffer->SetConstantBuffer(brushBuffer->Buffer());
	}
	
	if (sLineColorBuffer != NULL)
	{
		lineColorBuffer->Apply();
		sLineColorBuffer->SetConstantBuffer(lineColorBuffer->Buffer());
	}

	shader->DrawIndexed(0, Pass(), indexCount);
}

void Terrain::BaseMap(wstring file)
{
	SafeDelete(baseMap);

	baseMap = new Texture(file);
	sBaseMap->SetResource(baseMap->SRV());
}

void Terrain::LayerMap(wstring layer, wstring alpha)
{
	SafeDelete(layerMap);
	SafeDelete(alphaMap);

	layerMap = new Texture(layer);
	alphaMap = new Texture(alpha);

	sLayerMap->SetResource(layerMap->SRV());
	sAlphaMap->SetResource(alphaMap->SRV());
	
}

float Terrain::GetHeight(Vector3 position)
{
	// position
	UINT x = position.x;
	UINT z = position.z;

	if (x < 0 || x > width) return -1.0f;
	if (z < 0 || z > height) return -1.0f;

	// index
	UINT index[4];
	index[0] = width * (z + 0) + (x + 0);
	index[1] = width * (z + 1) + (x + 0);
	index[2] = width * (z + 0) + (x + 1);
	index[3] = width * (z + 1) + (x + 1);

	// vertex
	Vector3 v[4];

	for (int i = 0; i < 4; i++)
	{
		v[i] = vertices[index[i]].Position;
	}

	float ddx = (position.x - v[0].x) / 1.0f;
	float ddz = (position.z - v[0].z) / 1.0f;

	Vector3 temp;
	if (ddx + ddz <= 1)
	{
		temp = v[0] + (v[2] - v[0]) * ddx + (v[1] - v[0]) * ddz;
	}
	else
	{
		ddx = 1 - ddx;
		ddz = 1 - ddz;
		temp = v[3] + (v[1] - v[3]) * ddx + (v[2] - v[3]) * ddz;
	}

	return temp.y;
}

float Terrain::GetPickedHeight(Vector3 & position)
{
	// position
	UINT x = (UINT)position.x;
	UINT z = (UINT)position.z;

	if (x < 0 || x > width) return -1.0f;
	if (z < 0 || z > height) return -1.0f;

	// index
	UINT index[4];
	index[0] = width * (z + 0) + (x + 0);
	index[1] = width * (z + 1) + (x + 0);
	index[2] = width * (z + 0) + (x + 1);
	index[3] = width * (z + 1) + (x + 1);

	// vertex
	Vector3 p[4];

	for (int i = 0; i < 4; i++)
	{
		p[i] = vertices[index[i]].Position;
	}

	float u, v, distance;

	Vector3 start(position.x, 1000.0f, position.z);
	Vector3 direction(0, -1, 0);

	Vector3 result(-1, -1, -1);

	// leftdown
	if (D3DXIntersectTri(&p[0], &p[1], &p[2], &start, &direction, &u, &v, &distance) == TRUE)
		result = p[0] + (p[1] - p[0]) * u + (p[2] - p[0]) * v;

	// rightdown
	if (D3DXIntersectTri(&p[3], &p[1], &p[2], &start, &direction, &u, &v, &distance) == TRUE)
		result = p[3] + (p[1] - p[3]) * u + (p[2] - p[3]) * v;

	return result.y;
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
	Context::Get()->GetViewport()->Unproject(&n, mouse, world, V, P);

	mouse.z = 1.0f;
	Context::Get()->GetViewport()->Unproject(&f, mouse, world, V, P);
	
	direction = f - n;
	start = n;

	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width - 1; x++)
		{
			UINT index[4];
			index[0] = width * (z + 0) + (x + 0);
			index[1] = width * (z + 1) + (x + 0);
			index[2] = width * (z + 0) + (x + 1);
			index[3] = width * (z + 1) + (x + 1);

			Vector3 p[4];

			for (int i = 0; i < 4; i++)
			{
				p[i] = vertices[index[i]].Position;
			}

			float u, v, distance;

			// left down
			if (D3DXIntersectTri(&p[0], &p[1], &p[2], &start, &direction,
				&u, &v, &distance) == TRUE)
				return p[0] + (p[1] - p[0]) * u + (p[2] - p[0]) * v;
			
			// righ up
			if (D3DXIntersectTri(&p[3], &p[1], &p[2], &start, &direction,
				&u, &v, &distance) == TRUE)
				return p[3] + (p[1] - p[3]) * u + (p[2] - p[3]) * v;
		}
	}

	return Vector3(-1, - 1, - 1);
}

void Terrain::RaiseHeight(Vector3 & position, UINT type, UINT range)
{
	D3D11_BOX box;

	box.left = (UINT)position.x - range;
	box.top = (UINT)position.z + range;
	box.right = (UINT)position.x + range;
	box.bottom = (UINT)position.z - range;

	if (box.left < 0) box.left = 0;
	if (box.top > height) box.top = height;
	if (box.right > width) box.right = width;
	if (box.bottom < 0) box.bottom = 0;

	for (UINT z = box.bottom; z <= box.top; z++)
	{
		for (UINT x = box.left; x <= box.right; x++)
		{
			UINT index = width * z + x;
			vertices[index].Position.y += 5.0f * Time::Delta();
		}
	}
	CreateNormalData();
	/*{
		D3D::GetDC()->UpdateSubresource(vertexBuffer->Buffer(),
			0, NULL, vertices, sizeof(TerrainVertex)* vertexCount, 0);
	}*/
	{
		D3D11_MAPPED_SUBRESOURCE subResource;

		D3D::GetDC()->Map(vertexBuffer->Buffer(),
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&subResource);
		memcpy(subResource.pData, vertices, sizeof(TerrainVertex)*vertexCount);
		D3D::GetDC()->Unmap(vertexBuffer->Buffer(), 0);
	}
}
