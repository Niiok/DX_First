#include "Framework.h"
#include "DrawTerrain.h"

void DrawTerrain

void DrawTerrain::Update()
{
	static Vector3 direction(-1, -1, 1);
	ImGui::Slider
}

void DrawTerrain::Render()
{
	Vector3 position = terrain->GetPickedPosition();
	string text = "("
		+ to_string(position.x) + ","
		+ to_string(position.y) + ","
		+ to_string(position.z) +
		")";
	Gui::Get()->RenderText(10, 100, 1, 0, 0, text);

	//static Vector3 position(1, 2, 1);
	//if (Keyboard::Get()->Press('A'))
	//	position.x -= 10.0f * Time::Delta();
	//if (Keyboard::Get()->Press('D'))
	//	position.x += 10.0f * Time::Delta();

	


	Matrix world;
	D3DXMatrixIdentity(&world);
	Matrix V, P;
	V = Context::Get()->View();
	P = Context::Get()->Projection();

	Vector3 projection;
	sphere->Position(&position);
	position.y += 2.0f;
	Context::Get()->Get()->GetViewport()->Project(&project, position, world, V, P);

	Gui::Get()->RenderText(project.x, project.y, 0, 0, 1, "Test");

	terrain->Render();
	sphere->Render();
}
