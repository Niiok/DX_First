#include "Framework.h"
#include "RenderModel.h"
#include "Viewer/FreeCam.h"
#include "Environment/Terrain.h"

void RenderModel::Initialize()
{
	((FreeCam*)Context::Get()->GetCamera())->Speed(40, 2);
	Context::Get()->GetCamera()->RotationDegree(0, 0, 0);
	Context::Get()->GetCamera()->Position(0, 0, -20);

	tankRender = NULL;
	shader = new Shader(L"014_Model.fx");

	ReadTank();
	ReadTower();
}

void RenderModel::Ready()
{
}

void RenderModel::Destroy()
{
}

void RenderModel::Update()
{
	if (tankRender != NULL)
	{
		tankRender->Update();
	}
}

void RenderModel::Render()
{
	if (tankRender != NULL)
	{
		tankRender->Render();
	}
}

void RenderModel::ReadTank()
{
	tank = new Model();
	tank->ReadMaterial(L"Tank/Tank");
	tank->ReadMesh(L"Tank/Tank");
	int breakpoint = 999;

	tankRender = new ModelRender(shader, tank);
}

void RenderModel::ReadTower()
{
	tower = new Model();
	tower->ReadMaterial(L"Tower/Tower");
	int breakpoint = 999;
}
