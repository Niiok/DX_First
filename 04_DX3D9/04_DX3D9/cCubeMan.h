#pragma once
#include "cCharacter.h"
class cCubeMan :
	public cCharacter
{
public:
	cCubeMan();
	virtual ~cCubeMan();

protected:
	class cCubeNode* m_pRoot;
	D3DMATERIAL9	 m_stMt1;
	LPDIRECT3DTEXTURE9	m_pTexture;

	cCubeNode* m_leftArm;
	cCubeNode* m_rightArm;
	cCubeNode* m_leftLeg;
	cCubeNode* m_rightLeg;

public:
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;


};

