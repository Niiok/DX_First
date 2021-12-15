#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh(Shader * shader) 
	: Renderer(shader)
{
}

Mesh::~Mesh()
{
	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);
}

void Mesh::Render()
{
	if (vertexBuffer == NULL && indexBuffer == NULL)
	{
		Create();
		vertexBuffer = new VertexBuffer(vertices, vertexCount, sizeof(MeshVertex));
		indexBuffer = new IndexBuffer(indices, indexCount);
	}

	UINT stride = sizeof(MeshVertex);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Renderer::Render();


}

void Mesh::Position(float x, float y, float z)
{
	Position(D3DXVECTOR3(x, y, z));
}

void Mesh::Position(D3DXVECTOR3 & vec)
{
	position = vec;
	UpdateWorld();
}

void Mesh::Position(D3DXVECTOR3 * vec)
{
	*vec = position;
}

void Mesh::Rotation(float x, float y, float z)
{
	Rotation(D3DXVECTOR3(x, y, z));
}

void Mesh::Rotation(D3DXVECTOR3 & vec)
{
	rotation = vec;
	UpdateWorld();
}

void Mesh::Rotation(D3DXVECTOR3 * vec)
{
	*vec = rotation;
}

void Mesh::RotationDegree(float x, float y, float z)
{
}

void Mesh::RotationDegree(D3DXVECTOR3 & vec)
{
}

void Mesh::RotationDegree(D3DXVECTOR3 * vec)
{
}

void Mesh::Scale(float x, float y, float z)
{
	Scale(D3DXVECTOR3(x, y, z));
}

void Mesh::Scale(D3DXVECTOR3 & vec)
{
	scale = vec;
	UpdateWorld();
}

void Mesh::Scale(D3DXVECTOR3 * vec)
{
	*vec = scale;
}

void Mesh::Matrix(D3DXMATRIX * mat)
{
	memcpy(mat, &world, sizeof(D3DXMATRIX));
}

void Mesh::Color(D3DXCOLOR & val)
{
	color = val;
}

void Mesh::Color(float r, float g, float b)
{
	Color(D3DXCOLOR(r, g, b, 1.0f));
}

void Mesh::Create()
{
}

void Mesh::CreateBuffer()
{

}

void Mesh::UpdateWorld()
{
	D3DXMATRIX S, R, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	world = S * R * T;
}
