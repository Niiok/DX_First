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

public:
	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;


};

