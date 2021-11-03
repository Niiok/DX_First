#pragma once


class cMainGame
{
public :
	cMainGame();
	~cMainGame();

private:
	std::vector<ST_PC_VERTEX>	m_vecLineVertex;
	std::vector<ST_PC_VERTEX>	m_vecTriangleVertex;
	class cCubePC* m_pCubePC;
	class cCamera* m_pCamera;
	//class cGrid* m_pGrid;
	class cCubeMan* m_pCubeMan;
	std::vector<class cGroup*> m_vecGroup;

	LPDIRECT3DTEXTURE9 m_pTexture;
	std::vector<ST_PT_VERTEX> m_vecVertex;

	std::vector<class cGroup*> m_vecMap;
	iMap* m_pMap;

public:
	void Setup();
	void Update();
	void Render();

	void Set_Light();
	void Set_Texture();
	void Draw_Texture();

	void Setup_Obj();
	void Draw_Obj();

	void Setup_Map();
	void Draw_Map();
	void Setup_Surface();

	void WndProc(HWND hWNd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_Line();
	void Draw_Line();

	void Setup_Triangle();
	void Draw_Triangle();

};

