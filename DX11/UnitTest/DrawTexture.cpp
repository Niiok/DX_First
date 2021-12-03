#include "stdafx.h"
#include "DrawTexture.h"
#include "Viewer/FreeCam.h"

void DrawTexture::Initialize()
{
	//((FreeCam*)Context::Get()->GetCamera())->Speed(40, 0.5f);

	Context::Get()->GetCamera()->Position(0, 0, -3);
	shader = new Shader(L"005_Texture.fx");


	// vertex
	VertexTexture vertices[4];
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = Vector2(0.0f, 1.0f);
	vertices[1].Uv = Vector2(0.0f, 0.0f);
	vertices[2].Uv = Vector2(1.0f, 1.0f);
	vertices[3].Uv = Vector2(1.0f, 0.0f);

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VertexTexture) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
		//Color = Color(0, 0, 0, 1);
	}


	// index
	UINT indices[6] = { 0,1,2,  2,1,3 };

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

	/*D3DX11CreateShaderResourceViewFromFile(
		D3D::GetDevice(), L"../../_Textures/Box.png", NULL, NULL, &srv, NULL);

	shader->AsSRV("Map")->SetResource(srv);*/

	texture = new Texture(L"Box.png");
	shader->AsSRV("Map")->SetResource(texture->SRV());
}

void DrawTexture::Ready()
{
}

void DrawTexture::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void DrawTexture::Update()
{
	//ImGui::ColorEdit3("Color", (float*)&Color);
	//shader->AsVector("Color")->SetFloatVector(Color);

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

void DrawTexture::PreRender()
{
}

void DrawTexture::Render()
{
	UINT stride = sizeof(VertexTexture);
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

	shader->DrawIndexed(0, 0, indexCount);

	/*{
		static Vector3 position(1, 0, 0);


		Matrix world;
		D3DXMatrixTranslation(&world, position.x, position.y, position.z);

		Color Color(1, 0, 0, 1);

		shader->AsVector("Color")->SetFloatVector(Color);
		shader->AsMatrix("World")->SetMatrix(world);
		shader->Draw(0, 0, 4);
	}
	{
		static Vector3 position(-1, 0, 0);


		Matrix world2;
		D3DXMatrixTranslation(&world2, position.x, position.y, position.z);

		Color Color(1, 0, 0, 1);

		shader->AsVector("Color")->SetFloatVector(Color);
		shader->AsMatrix("World")->SetMatrix(world2);
		shader->Draw(0, 0, 4);
	}*/

	//ImGui::Text("FPS : %f", 0.1f);
}

void DrawTexture::PostRender()
{
}

void DrawTexture::ResizeScreen()
{
}
