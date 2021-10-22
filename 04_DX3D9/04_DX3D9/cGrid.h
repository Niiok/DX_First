#pragma once

class cGrid
{
public :
	cGrid();
	~cGrid();

private:
	std::vector<ST_PC_VERTEX>		m_vecVertex;
	std::vector<class cPyramid*>	m_vecPyramid;

public:
	//void Setup(int nNumHalfTile);	// lost
	//void Render();

};

