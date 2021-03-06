#include "Framework.h"
#include "Context.h"
#include "Viewer/Viewport.h"
#include "Viewer/Perspective.h"
#include "Viewer/FreeCam.h"

Context* Context::instance = NULL;

Context * Context::Get()
{
	assert(instance != NULL);

	return instance;
}

void Context::Create()
{
	assert(instance == NULL);

	instance = new Context();
}

void Context::Delete()
{
	SafeDelete(instance);
}

Context::Context()
{
	D3DDesc desc = D3D::GetDesc();

	perspective = new Perspective(desc.Width, desc.Height);
	viewport = new Viewport(desc.Width, desc.Height);
	camera = new FreeCam();

	//position = D3DXVECTOR3(29.5f, 16.5f, -50.0f);
	/*position = D3DXVECTOR3(0, 4, -10);
	D3DXVECTOR3 forward(0, 0, 1);
	D3DXVECTOR3 right(1, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);*/

	//D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);
}

Context::~Context()
{
	SafeDelete(perspective);
	SafeDelete(viewport);
	SafeDelete(camera);
}

void Context::Update()
{
	camera->Update();
}

void Context::Render()
{
	/*ImGui::SliderFloat3("Camera", (float*)&position, -100, 100);
	D3DXVECTOR3 forward(0, 0, 1);
	D3DXVECTOR3 right(1, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	
	D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);*/

	viewport->RSSetViewport();
}

D3DXMATRIX Context::View()
{
	Matrix view;
	camera->GetMatrix(&view);
	return view;
}

D3DXMATRIX Context::Projection()
{
	D3DXMATRIX projection;
	perspective->GetMatrix(&projection);

	return projection;
}
