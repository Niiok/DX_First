#include "framework.h"
#include "cGrid.h"
#include "cGizmo.h"
//
//cGrid::cGrid()
//{
//}
//
//cGrid::~cGrid()
//{
//	for(auto p : m_vecGizmo)
//	{
//		Safe_Delete(p);
//	}
//	m_vec
//}
//
//void cGrid::Setup(int nNumHalfTile, float fInterval)
//{
//	float fMax = nNumHalfTile * fInterval;
//	float fMin = -fMax;
//
//	ST_PC_VERTEX v;
//
//	for (int i = 1; i <= nNumHalfTile; ++i)
//	{
//		if (i % 5 == 0)
//			v.c = D3DCOLOR_XRGB(255, 255, 255);
//		else
//			v.c = D3DCOLOR_XRGB(128, 128, 128);
//
//		v.p = D3DXVECTOR3(fMin, 0, i * fInterval); m_vecVertex.push_back(v);
//		v.p = D3DXVECTOR3(fMin, 0, i * fInterval); m_vecVertex.push_back(v);
//
//		cpntext = D3D
//
//
//	}
//	cGizmo* pGizmo = NULL;
//	D3DXMATRIXA16 matR;
//
//	pGizmo = new cGizmo;
//	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
//	pGizmo->
//}
//
//
//void cGrid::Render()
//{
//
//
//
//	///////
//
//	D3DXMATRIXA16 matI;
//	D3DXMatrixIdentity(&matI);
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
//	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vec)
//