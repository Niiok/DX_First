#pragma once
#include "framework.h"



class cMainGame
{
public :
	cMainGame();
	~cMainGame();

private:
	HDC		mem_dc_;
	HBITMAP	h_old_bitmap_, h_bitmap_;

	vector<RowVector4f>	vec_vertex_;
	vector<DWORD>		vec_index_;
	vector<RowVector4f>	vec_line_vertex_;

	Matrix4f			mat_world_;
	Matrix4f			mat_view_;
	Matrix4f			mat_proj_;
	Matrix4f			mat_viewport_;

	RowVector4f			v_eye_;
	RowVector4f			v_look_at_;
	RowVector4f			v_up_;

public :
	void SetUp();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

