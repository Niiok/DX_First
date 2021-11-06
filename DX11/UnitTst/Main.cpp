#include "stdafx.h"
#include "Main.h"
#include "Systems/Window.h"



void Main::Initialize()
{
	/*for (IExecute* exe : executes)
	{
		exe->Initialize();
	}*/
}

void Main::Ready()
{
	/*for (IExecute* exe : executes)
	{
		exe->Ready();
	}*/
}

void Main::Destroy()
{
	for (IExecute* exe : executes)
	{
		exe->Destroy();
		SafeDelete(exe);
	}
}

void Main::Update()
{
	for (IExecute* exe : executes)
	{
		exe->Update();
	}
}

void Main::PreRender()
{
	for (IExecute* exe : executes)
	{
		exe->PreRender();
	}
}

void Main::Render()
{
	for (IExecute* exe : executes)
	{
		exe->Render();
	}
}

void Main::PostRender()
{
	for (IExecute* exe : executes)
	{
		exe->PostRender();
	}
}

void Main::ResizeScreen()
{
	for (IExecute* exe : executes)
	{
		exe->ResizeScreen();
	}
}

void Main::Push(IExecute * execute)
{
	executes.push_back(execute);
}
