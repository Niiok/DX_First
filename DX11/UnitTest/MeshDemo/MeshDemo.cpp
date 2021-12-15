#include "Framework.h"
#include "MeshDemo.h"
#include "Viewer/FreeCam.h"
#include "Environment/Terrain.h"


void MeshDemo::Initialize()
{
	Context::Get()->GetCamera()->Position(0, 60, -80);
	Context::Get()->GetCamera()->RotationDegree(33, 0, 0);

	shader = new Shader(L"015_Mesh.fx");

	// mesh
	floor = new Material(shader);
	floor->DiffuseMap("Floor.png");

	stone = new Material(shader);
	stone->DiffuseMap("Stone.png");
	
	brick = new Material(shader);
	brick->DiffuseMap("Brick.png");
	
	wall = new Material(shader);
	wall->DiffuseMap("Wall.png");


	cube = new MeshCube(shader);
	cube->GetTransform()->Position(0, 5.0f, 0);
	cube->GetTransform()->Scale(15.0f, 5.0f, 15.0f);

	grid = new MeshGrid(shader, 3, 3);
	grid->GetTransform()->Position(0, 0, 0);
	grid->GetTransform()->Scale(20, 1, 20);

	for (UINT i = 0; i < 5; i++)
	{
		cylinder[i * 2] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2]->GetTransform()->Position(-30, 6.0f, -15.0f + (float)i* 15.0f);
		cylinder[i * 2]->GetTransform()->Scale(5, 5, 5);
		
		cylinder[i * 2 + 1] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2 + 1]->GetTransform()->Position(30, 6.0f, -15.0f + (float)i* 15.0f);
		cylinder[i * 2 + 1]->GetTransform()->Scale(5, 5, 5);

		sphere[i * 2] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2]->GetTransform()->Position(-30, 15.0f, -15.0f + (float)i * 15.0f);
		sphere[i * 2]->GetTransform()->Scale(5, 5, 5);
		
		sphere[i * 2 + 1] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2 + 1]->GetTransform()->Position(30, 15.0f, -15.0f + (float)i * 15.0f);
		sphere[i * 2 + 1]->GetTransform()->Scale(5, 5, 5);
	}
}


void MeshDemo::Update()
{
	for (UINT i = 0; i < 10; i++)
	{
		cylinder[i]->Update();
		sphere[i]->Update();
	}

	cube->Update();
	grid->Update();
}

void MeshDemo::Render()
{
	wall->Render();
	for (UINT i = 0; i < 10; i++)
		sphere[i]->Render();
	
	brick->Render();
	for (UINT i = 0; i < 10; i++)
		cylinder[i]->Render();

	stone->Render();
	cube->Render();


}
