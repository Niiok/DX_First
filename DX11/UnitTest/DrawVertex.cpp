#include "stdafx.h"
#include "DrawVertex.h"
#include "Viewer/FreeCam.h"

void DrawVertex::Initialize()
{
	((FreeCam*)Context::Get()->GetCamera())->Speed(40, 2);

	shader = new Shader(L"004_Quad.fx");


	// vertex
	vertexCount = (width + 1) * (height + 1);
	vertices = new Vertex[vertexCount];

	for (UINT z = 0; z <= height; z++)
	{
		for (UINT x = 0; x <= width; x++)
		{
			UINT index = (width + 1)*z + x;
			vertices[index].Position.x = (float)x;
			vertices[index].Position.y = 0.0f;
			vertices[index].Position.z = (float)z;
		}
	}

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
		color = Color(0, 0, 0, 1);
	}


	// index
	indexCount = width * height * 6;
	indices = new UINT[indexCount];

	UINT index = 0;
	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			indices[index + 0] = (width + 1)* (z + 0) + x + 0;
			indices[index + 1] = (width + 1)* (z + 1) + x + 0;
			indices[index + 2] = (width + 1)* (z + 0) + x + 1;

			indices[index + 3] = (width + 1)* (z + 0) + x + 1;
			indices[index + 4] = (width + 1)* (z + 1) + x + 0;
			indices[index + 5] = (width + 1)* (z + 1) + x + 1;

			index += 6;
		}
	}

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}
}

void DrawVertex::Ready()
{
}

void DrawVertex::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void DrawVertex::Update()
{
	ImGui::ColorEdit3("Color", (float*)&color);
	shader->AsVector("Color")->SetFloatVector(color);

	Vector3 camRot;
	Context::Get()->GetCamera()->Rotation(&camRot);
	ImGui::InputFloat3("CamRot", (float*)&camRot);
	ImGui::DragFloat3("CamRot Drag", (float*)&camRot);
	Context::Get()->GetCamera()->Rotation(camRot);

	Vector3 camPos;
	Context::Get()->GetCamera()->Position(&camPos);
	ImGui::InputFloat3("CamPos", (float*)&camPos);
	ImGui::DragFloat3("CamPos Drag", (float*)&camPos);
	Context::Get()->GetCamera()->Position(camPos);
	
	
	ImGui::InputInt("Number", (int*)&number);
	number %=vertexCount;

	if (Keyboard::Get()->Press(VK_LEFT))
		vertices[number].Position.x -= 2.0f * Time::Delta();
	else if(Keyboard::Get()->Press(VK_RIGHT))
		vertices[number].Position.x += 2.0f * Time::Delta();

	if (Keyboard::Get()->Press(VK_UP))
		vertices[number].Position.y += 2.0f * Time::Delta();
	else if(Keyboard::Get()->Press(VK_DOWN))
		vertices[number].Position.y -= 2.0f * Time::Delta();

	D3D::GetDC()->UpdateSubresource(vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 4, 0);

	Matrix world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&world, 2, 2, 1);
	/*{
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
	}*/
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
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	static bool bWireframe = false;
	ImGui::Checkbox("Wirefreme", &bWireframe);

	/*if (bWireframe)
		shader->Draw(0, 0, 6);
	else
		shader->Draw(0, 1, 6);*/

	shader->DrawIndexed(0, (bWireframe ? 0 : 1), indexCount);

	/*{
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
	}*/

	//ImGui::Text("FPS : %f", 0.1f);
}

void DrawVertex::PostRender()
{
}

void DrawVertex::ResizeScreen()
{
}
