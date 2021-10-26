#pragma once
class cCubePNT
{
public:
	cCubePNT();
	virtual ~cCubePNT();
	
protected:
	std::vector<ST_PNT_VERTEX>	m_vecVertex;

public:
	virtual void SetUp();
	virtual void Update();
	virtual void Render();


};

