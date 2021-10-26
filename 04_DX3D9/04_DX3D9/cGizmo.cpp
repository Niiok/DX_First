#include "framework.h"
#include "cGizmo.h"

cGizmo::cGizmo()
{
}

cGizmo::~cGizmo()
{
}

void cGizmo::Setup(D3DCOLOR c, D3DXMATRIXA16 & mat)
{
	m_matR = mat;
	ST_PC_VERTEX v;

	v.c = c;

	v.p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(v);
	// 1, -1, -1
	// -1, -1, -1
	
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
