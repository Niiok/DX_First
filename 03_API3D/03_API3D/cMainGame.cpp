#include "cMainGame.h"

cMainGame::cMainGame()
	:h_bitmap_(NULL), v_eye_(0,0,-5,1),
	v_look_at_(0,0,0,1), v_up_(0,1,0,1)
{
}

cMainGame::~cMainGame()
{
	SelectObject(mem_dc_, h_old_bitmap_);
	DeleteObject(h_bitmap_);
	DeleteDC(mem_dc_);
}

void cMainGame::SetUp()
{
	HDC hdc = GetDC(_hWnd);
	mem_dc_ = CreateCompatibleDC(hdc);

	RECT rc;
	GetClientRect(_hWnd, &rc);
	h_bitmap_ = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	h_old_bitmap_ = (HBITMAP)SelectObject(mem_dc_, h_bitmap_);
	ReleaseDC(_hWnd, hdc);

	//	    5 ------ 6
	//	1 --+--- 2   |
	//	|   |  * |   |
 	//  |   4 ---+-- 7
	//	0 ------ 3

	vec_vertex_.push_back(RowVector4f(-1.0f, -1.0f, -1.0f, 1));	// 0
	vec_vertex_.push_back(RowVector4f(-1.0f, 1.0f, -1.0f, 1));	// 1
	vec_vertex_.push_back(RowVector4f(1.0f, 1.0f, -1.0f, 1));		// 2
	vec_vertex_.push_back(RowVector4f(1.0f, -1.0f, -1.0f, 1));	// 3

	vec_vertex_.push_back(RowVector4f(-1.0f, -1.0f, 1.0f, 1));	// 4
	vec_vertex_.push_back(RowVector4f(-1.0f, 1.0f, 1.0f, 1));		// 5
	vec_vertex_.push_back(RowVector4f(1.0f, 1.0f, 1.0f, 1));		// 6
	vec_vertex_.push_back(RowVector4f(1.0f, -1.0f, 1.0f, 1));		// 7

	// front
	vec_index_.push_back(0);
	vec_index_.push_back(1);
	vec_index_.push_back(2);

	vec_index_.push_back(0);
	vec_index_.push_back(2);
	vec_index_.push_back(3);

	// back
	vec_index_.push_back(4);
	vec_index_.push_back(6);
	vec_index_.push_back(5);

	vec_index_.push_back(4);
	vec_index_.push_back(7);
	vec_index_.push_back(6);
//		r 326 267


	// left
	vec_index_.push_back(4);
	vec_index_.push_back(5);
	vec_index_.push_back(1);
	
	vec_index_.push_back(4);
	vec_index_.push_back(1);
	vec_index_.push_back(0);

	// top
	vec_index_.push_back(1);
	vec_index_.push_back(5);
	vec_index_.push_back(6);
	
	vec_index_.push_back(1);
	vec_index_.push_back(6);
	vec_index_.push_back(2);


	// bottom
	vec_index_.push_back(4);
	vec_index_.push_back(0);
	vec_index_.push_back(3);

	vec_index_.push_back(4);
	vec_index_.push_back(3);
	vec_index_.push_back(7);

	mat_world_ = Matrix4f::Identity();
	mat_view_ = Matrix4f::Identity();
	mat_proj_ = Matrix4f::Identity();
	mat_viewport_ = Matrix4f::Identity();
}

void cMainGame::Update()
{
	RECT rc;
	GetClientRect(_hWnd, &rc);

	v_look_at_ = RowVector4f(0.0f, 0.0f, 0.0f, 1);
	v_eye_ = RowVector4f(0.0f, 5.0f, -5.0f, 1);

	//mat_view_ = Matrix.View(v_eye_, v_look_at_, v_up_);
	//mat_proj_ = projection(PI/4.0f, (float)rc.right/ rc.bottom,
					//1.0f, 1000.0f)'

	//mat_viewport_ = viewport(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(_hWnd, &rc);

	PatBlt(mem_dc_, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	Matrix4f matWVP = mat_world_ * mat_view_ * mat_proj_;

	for (size_t i = 0; i < vec_index_.size(); i += 3)
	{
		RowVector4f v1 = vec_vertex_[vec_index_[i + 0]];
		RowVector4f v2 = vec_vertex_[vec_index_[i + 1]];
		RowVector4f v3 = vec_vertex_[vec_index_[i + 2]];

		//v1 = TransformCoord(v1, matMVP);
		v1 = v1 * matWVP;
		//v2 = TransformCoord(v2, matMVP);
		v2 = v2 * matWVP;
		//v3 = TransformCoord(v3, matMVP);
		v3 = v3 * matWVP;
		
		// todo

		//v1 = TransformCoord(v1, mat_viewport_);
		v1 = v1 * mat_viewport_;
		//v2 = TransformCoord(v2, mat_viewport_);
		v2 = v2 * mat_viewport_;
		//v3 = TransformCoord(v3, mat_viewport_);
		v3 = v3 * mat_viewport_;

		MoveToEx(mem_dc_, v1(0), v1(1), NULL);
		LineTo(mem_dc_, v2(0), v2(1));
		LineTo(mem_dc_, v3(0), v3(1));
		LineTo(mem_dc_, v1(0), v1(1));
	}

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, mem_dc_, 0, 0, SRCCOPY);
}


void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
