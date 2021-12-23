#include "Framework.h"
#include "Sky.h"

Sky::Sky()
	: cubeSRV(NULL)
{
	shader = new Shader(L"018_Sky.fx");
	buffer = new ConstantBuffer(&desc, sizeof(Desc));
	sBuffer = shader->AsConstantBuffer("CB_Sky");
	sphere = new MeshSphere(shader, 0.5f);
}

Sky::Sky(wstring cubeMapFile)
{
	shader = new Shader(L"018_Sky.fx");
	buffer = new ConstantBuffer(&desc, sizeof(Desc));
	sBuffer = shader->AsConstantBuffer("CB_Sky");
	sphere = new MeshSphere(shader, 0.5f);

	sphere->GetTransform()->Scale(1000, 1000, 1000);
	sphere->Pass(2);

	wstring temp = L"../../_Texture/" + cubeMapFile;
	Check(
		D3DX11CreateShaderResourceViewFromFile(
		D3D::GetDevice(), temp.c_str(), NULL, NULL, &cubeSRV, NULL)
	);

	sCubeSRV = shader->AsSRV("SkyCubeMap");
}

Sky::~Sky()
{
	SafeDelete(shader);
	SafeDelete(sphere);
	SafeDelete(buffer);
}

void Sky::Update()
{
	ImGui::ColorEdit3("Center", (float*)&desc.Center);
	ImGui::ColorEdit3("Apex", (float*)&desc.Apex);
	ImGui::InputFloat("Sky Height", &desc.Height, 0.1f);

	Vector3 position;
	Context::Get()->GetCamera()->Position(&position);
	sphere->GetTransform()->Position(position);

	sphere->Update();
}

void Sky::Render()
{
	buffer->Apply();
	sBuffer->SetConstantBuffer(buffer->Buffer());
	sCubeSRV->SetResource(cubeSRV);

	sphere->Render();
}
