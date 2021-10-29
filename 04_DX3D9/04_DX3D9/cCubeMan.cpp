#include "framework.h"
#include "cCubeMan.h"
#include "cCubeNode.h"

#include "cBody.h"
#include "cHead.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL)
	, m_pTexture(NULL)
{
}

cCubeMan::~cCubeMan()
{
	if (m_pRoot)
		m_pRoot->Destroy();

	SAFE_RELEASE(m_pTexture);
}

void cCubeMan::Setup()
{
	cCharacter::Setup();

	D3DXCreateTextureFromFile(g_pD3DDevice, L"steve.png", &m_pTexture);

	ZeroMemory(&m_stMt1, sizeof(D3DMATERIAL9));
	m_stMt1.Ambient	 = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMt1.Diffuse	 = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMt1.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	cBody* pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = pBody;
	
	cHead* pHead = new cHead;
	pHead->Setup();
	m_pRoot->AddChild(pHead);

	m_leftArm = new cLeftArm;
	m_leftArm->Setup();
	m_leftArm->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(m_leftArm);

	m_rightArm = new cRightArm;
	m_rightArm->Setup();
	m_rightArm->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(m_rightArm);

	m_leftLeg = new cLeftLeg;
	m_leftLeg->Setup();
	m_leftLeg->SetRotDeltaX(-0.1f);
	m_pRoot->AddChild(m_leftLeg);

	m_rightLeg = new cRightLeg;
	m_rightLeg->Setup();
	m_rightLeg->SetRotDeltaX(0.1f);
	m_pRoot->AddChild(m_rightLeg);
}

void cCubeMan::Update()
{
	cCharacter::Update();

	if (m_vVelocity == D3DXVECTOR3(0, 0, 0))
	{
		m_leftArm->SetRotX(-m_leftArm->GetRotDeltaX());
		m_rightArm->SetRotX(-m_rightArm->GetRotDeltaX());
		m_leftLeg->SetRotX(-m_leftLeg->GetRotDeltaX());
		m_rightLeg->SetRotX(-m_rightLeg->GetRotDeltaX());
	}

	if (m_pRoot)
		m_pRoot->Update();
}

void cCubeMan::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetMaterial(&m_stMt1);

		g_pD3DDevice->SetTexture(0, m_pTexture);
		cCharacter::Render();

		//D3DXMATRIXA16 matWorld;
		//D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

		if (m_pRoot)
			m_pRoot->Render();

		g_pD3DDevice->SetTexture(0, NULL);
	}
}
