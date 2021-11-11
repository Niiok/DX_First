#include "stdafx.h"
#include "DrawVertex.h"

void DrawVertex::Initialize()
{
	shader = new Shader(L"003_World.fx");

	vertices[0].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[1].Position = Vector3(0.0f, 0.5f, 0.0f);

	vertices[2].Position = Vector3(0.5f, 0.0f, 0.0f);
	vertices[3].Position = Vector3(0.5f, 0.5f, 0.0f);

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(Vertex) * 4;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	color = Color(0, 0, 0, 1);
}

void DrawVertex::Ready()
{
}

void DrawVertex::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void DrawVertex::Update()
{
	ImGui::ColorEdit3("Color", (float*)&color);
	shader->AsVector("Color")->SetFloatVector(color);

	/*ImGui::InputInt("Number", (int*)&number);
	number %= 4;
	
	if (Keyboard::Get()->Press(VK_LEFT))
		vertices[number].Position.x -= 2.0f * Time::Delta();
	else if(Keyboard::Get()->Press(VK_RIGHT))
		vertices[number].Position.x += 2.0f * Time::Delta();
	
	if (Keyboard::Get()->Press(VK_UP))
		vertices[number].Position.y += 2.0f * Time::Delta();
	else if(Keyboard::Get()->Press(VK_DOWN))
		vertices[number].Position.y -= 2.0f * Time::Delta();

	D3D::GetDC()->UpdateSubresource(vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 4, 0);*/

	Matrix world;
	D3DXMatrixIdentity(&world);
	{
		static Vector3 position(0, 0, 0);

		if (Keyboard::Get()->Press(VK_LEFT))
			vertices[number].Position.x -= 1.0f * Time::Delta();
		else if (Keyboard::Get()->Press(VK_RIGHT))
			vertices[number].Position.x += 1.0f * Time::Delta();

		if (Keyboard::Get()->Press(VK_UP))
			vertices[number].Position.y += 1.0f * Time::Delta();
		else if (Keyboard::Get()->Press(VK_DOWN))
			vertices[number].Position.y -= 1.0f * Time::Delta();

		D3DXMatrixTranslation(&world, position.x, position.y, 0);
	}
	shader->AsMatrix("World")->SetMatrix(world);

	Matrix view = Context::Get()->View();
	shader->AsMatrix("View")->SetMatrix(view);

	Matrix projection = Context::Get()->Projection();
	shader->AsMatrix("Projection")->SetMatrix(projection);
}

void DrawVertex::PreRender()
{
}

void DrawVertex::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	shader->Draw(0, 0, 4);

	{
		static Vector3 position(1, 0, 0);
	

		Matrix world;
		D3DXMatrixTranslation(&world, position.x, position.y, position.z);

		Color color(1, 0, 0, 1);

		shader->AsVector("Color")->SetFloatVector(color);
		shader->AsMatrix("World")->SetMatrix(world);
		shader->Draw(0, 0, 4);
	}
	{
		static Vector3 position(-1, 0, 0);
	

		Matrix world2;
		D3DXMatrixTranslation(&world2, position.x, position.y, position.z);

		Color color(1, 0, 0, 1);

		shader->AsVector("Color")->SetFloatVector(color);
		shader->AsMatrix("World")->SetMatrix(world2);
		shader->Draw(0, 0, 4);
	}

	//ImGui::Text("FPS : %f", 0.1f);
}

void DrawVertex::PostRender()
{
}

void DrawVertex::ResizeScreen()
{
}
