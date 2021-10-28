#include "framework.h"
#include "cGizmo.h"

cGizmo::cGizmo()
{
}

cGizmo::~cGizmo()
{
}

void cGizmo::Setup(D3DXCOLOR c, D3DXMATRIXA16 & mat)
{
	ZeroMemory(&m_stMt1, sizeof(D3DMATERIAL9));
	m_stMt1.Ambient = c;
	m_stMt1.Diffuse = c;
	m_stMt1.Specular = c;

	m_matR = mat;
	ST_PC_VERTEX v;

	v.c = c;

	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(v);
	
	// 0, 0. 0
	// 1. -1. 1
	// 1 -1 -1


	//-1, -1, -1
	//1, -1, -1
	//-1, -1, 1

	// 1, -1, -1
	// 1, -1, 1
	// -1, -1, 1
		
}

void cGizmo::Render()
{
	D3DXMATRIXA16 matWorld, matS;

	
}
