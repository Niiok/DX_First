#include "Framework.h"
#include "DrawTerrain.h"
#include "Viewer/FreeCam.h"
#include "Environment/Terrain.h"


void DrawTerrain::Initialize()
{
	((FreeCam*)Context::Get()->GetCamera())->Speed(60, 10);

	//shader = new Shader(L"009_Terrain.fx");
	//shader = new Shader(L"010_Terrain.fx");
	//shader = new Shader(L"011_Terrain.fx");
	//shader = new Shader(L"012_TerrainGridLine.fx");
	shader = new Shader(L"013_Terrain_Splatting.fx");

	terrain = new Terrain(shader, L"HeightMap/HeightMapTest.png");
	//terrain = new Terrain(shader, L"Test2.png");
	terrain->BaseMap(L"Terrain/Dirt.png");

	terrain->LayerMap(L"Terrain/Grass (Lawn).png", L"HeightMap/AlphaMap256");


	////
	/*sphereShader = new Shader(L"007_Mesh.fx");
	sphere = new MeshSphere(sphereShader, 0.5f);
	sphere->Color(1, 0, 0);
	sphere->Position(0, 0, 0);*/
}

void DrawTerrain::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);
}

void DrawTerrain::Update()
{
	static Vector3 direction(-1, -1, 1);
	ImGui::SliderFloat("Light Direction", (float*)&direction, -1, 1);
	//shader->AsVector("LightDirection")->SetFloatVector(direction);
	//sphereShader->AsVector("LightDirection")->SetFloatVector(direction);
	Context::Get()->LightDirection(direction);


	//Vector3 position;
	////sphere->Position(&position);

	//if (Keyboard::Get()->Press(VK_UP))
	//	position.z += 30.0f * Time::Delta();
	//else if (Keyboard::Get()->Press(VK_DOWN))
	//	position.z -= 30.0f * Time::Delta();
	//
	//if (Keyboard::Get()->Press(VK_RIGHT))
	//	position.x += 30.0f * Time::Delta();
	//else if (Keyboard::Get()->Press(VK_LEFT))
	//	position.x -= 30.0f * Time::Delta();

	////position.y = terrain->GetHeight(position) + 0.5f;
	//position.y = terrain->GetPickedHeight(position) + 0.5f;

	//sphere->Position(position);

	/*if (Mouse::Get()->Down(0))
	{
		Vector3 position = terrain->GetPickedPosition();
		if (position.x >= 0.0f && position.z >= 0.0f)
		{
			position.y += 0.5f;
			sphere->Position(position);
		}
	}*/

	//position.y = terrain

	terrain->Update();
}

void DrawTerrain::Render()
{
	//Vector3 position = terrain->GetPickedPosition();
	//string text = "("
	//	+ to_string(position.x) + ","
	//	+ to_string(position.y) + ","
	//	+ to_string(position.z) +
	//	")";
	//Gui::Get()->RenderText(10, 100, 1, 0, 0, text);

	//static Vector3 position(1, 2, 1);
	//if (Keyboard::Get()->Press('A'))
	//	position.x -= 10.0f * Time::Delta();
	//if (Keyboard::Get()->Press('D'))
	//	position.x += 10.0f * Time::Delta();



	/*Vector3 project;

	Matrix world;
	D3DXMatrixIdentity(&world);
	Matrix V, P;
	V = Context::Get()->View();
	P = Context::Get()->Projection();

	Vector3 position;
	sphere->Position(&position);
	position.y += 2.0f;
	Context::Get()->Get()->GetViewport()->Project(&project, position, world, V, P);

	Gui::Get()->RenderText(project.x, project.y, 0, 0, 1, "Test");*/

	terrain->Render();
	//sphere->Render();
}
