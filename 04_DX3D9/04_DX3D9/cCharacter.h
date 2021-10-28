#pragma once
class cCharacter
{
public :
	cCharacter();
	virtual ~cCharacter();

protected:
	float m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;
	
	D3DXVECTOR3		m_vVelocity;

public:
	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual D3DXVECTOR3 GetPosition();
};

