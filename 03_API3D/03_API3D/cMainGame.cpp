#include "cMainGame.h"

cMainGame::cMainGame()
	:h_bitmap_(NULL), v_eye_(0, 0, -5, 1),
	v_look_at_(0, 0, 0, 1), v_up_(0, 1, 0, 1),
	v_position_(0, 0, 0, 1), box_rot_y_(0.0f),
	v_box_direction_(0, 0, 1, 1), camera_distance_(5),
	is_l_button_down_(false), v_cam_rot_angle_(0, 0, 0, 1),
	scale_(1)
{
	pt_prev_mouse_.x = 0;
	pt_prev_mouse_.y = 0;
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


	// right
	vec_index_.push_back(3);
	vec_index_.push_back(2);
	vec_index_.push_back(6);

	vec_index_.push_back(2);
	vec_index_.push_back(6);
	vec_index_.push_back(7);


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

	SetGrid();
}

void cMainGame::Update()
{
	Update_Rotation();
	Update_Move();
	Update_Scale();

	RECT rc;
	GetClientRect(_hWnd, &rc);
	
	Matrix4f mat_rx = EigenDX::Matrix::RotationX(v_cam_rot_angle_(0));
	Matrix4f mat_ry = EigenDX::Matrix::RotationY(v_cam_rot_angle_(1));
	Matrix4f mat_rc = mat_rx * mat_ry;

	v_look_at_ = v_position_;
	v_eye_ = RowVector4f(0.0f, camera_distance_, -camera_distance_, 1);
	v_eye_ = EigenDX::Vector::TransformCoord(v_eye_, mat_rc);
	v_eye_ += v_position_;


	// W = S x R x T
	Matrix4f mat_s = EigenDX::Matrix::Scale(scale_);
	Matrix4f mat_r = EigenDX::Matrix::RotationY(box_rot_y_);

	v_box_direction_ = RowVector4f(0, 0, 1, 1);
	v_box_direction_ *= EigenDX::Matrix::RotationY(box_rot_y_);

	mat_world_ = mat_s * mat_r * EigenDX::Matrix::Translation(v_position_);
	mat_view_ = EigenDX::Matrix::View(v_eye_, v_look_at_, v_up_);
	mat_proj_ = EigenDX::Matrix::Projection(PI / 4.0f, (float)rc.right / rc.bottom,
		1.0f, 1000.0f);

	mat_viewport_ = EigenDX::Matrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
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

		v1 = EigenDX::Vector::TransformCoord(v1, matWVP);
		//v1 = v1 * matWVP;
		v2 = EigenDX::Vector::TransformCoord(v2, matWVP);
		//v2 = v2 * matWVP;
		v3 = EigenDX::Vector::TransformCoord(v3, matWVP);
		//v3 = v3 * matWVP;

		// todo : culling
		/*if (IsBackFace(v1, v2, v3))
			continue;*/

		v1 = EigenDX::Vector::TransformCoord(v1, mat_viewport_);
		//v1 = v1 * mat_viewport_;
		v2 = EigenDX::Vector::TransformCoord(v2, mat_viewport_);
		//v2 = v2 * mat_viewport_;
		v3 = EigenDX::Vector::TransformCoord(v3, mat_viewport_);
		//v3 = v3 * mat_viewport_;

		MoveToEx(mem_dc_, v1(0), v1(1), NULL);
		LineTo(mem_dc_, v2(0), v2(1));
		LineTo(mem_dc_, v3(0), v3(1));
		LineTo(mem_dc_, v1(0), v1(1));
	}

	//DrawGrid();

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, mem_dc_, 0, 0, SRCCOPY);
}


void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		pt_prev_mouse_.x = LOWORD(lParam);
		pt_prev_mouse_.y = HIWORD(lParam);
		is_l_button_down_ = true;
		break;

	case WM_LBUTTONUP:
		is_l_button_down_ = false;
		break;

	case WM_MOUSEMOVE:
		if (is_l_button_down_)
		{
			POINT pt_cur_mouse;
			pt_cur_mouse.x = LOWORD(lParam);
			pt_cur_mouse.y = HIWORD(lParam);
			float delta_x = (float)pt_cur_mouse.x - pt_prev_mouse_.x;
			float delta_y = (float)pt_cur_mouse.y - pt_prev_mouse_.y;

			v_cam_rot_angle_(1) += (delta_x / 100.0f);
			v_cam_rot_angle_(0) += (delta_y / 100.0f);

			if (v_cam_rot_angle_(0) < -PI / 2.0f + 0.0001f)
				v_cam_rot_angle_(0) = -PI / 2.0f + 0.0001f;
			if (v_cam_rot_angle_(0) < PI / 2.0f + 0.0001f)
				v_cam_rot_angle_(0) = PI / 2.0f + 0.0001f;

			pt_prev_mouse_ = pt_cur_mouse;
		}
		break;

	case WM_MOUSEWHEEL:
		camera_distance_ -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);
		if (camera_distance_ < 0.000f)
			camera_distance_ = 0.0001f;
		break;

	default:
		break;
	}
}

void cMainGame::SetGrid()
{
	int n_num_half_tile = 5;
	float f_interval = 1.0f;
	float f_max = n_num_half_tile * f_interval;
	float f_min = -n_num_half_tile * f_interval;

	for (int i = 1; i <= n_num_half_tile; ++i)
	{		
		vec_grid_vertex_.push_back(RowVector4f(f_min, 0, i * f_interval, 1));
		vec_grid_vertex_.push_back(RowVector4f(f_max, 0, i * f_interval, 1));

		vec_grid_vertex_.push_back(RowVector4f(f_min, 0, -i * f_interval, 1));
		vec_grid_vertex_.push_back(RowVector4f(f_max, 0, -i * f_interval, 1));

		vec_grid_vertex_.push_back(RowVector4f(i * f_interval, 0, f_min, 1));
		vec_grid_vertex_.push_back(RowVector4f(i * f_interval, 0, f_max, 1));

		vec_grid_vertex_.push_back(RowVector4f(-i * f_interval, 0, f_min, 1));
		vec_grid_vertex_.push_back(RowVector4f(-i * f_interval, 0, f_max, 1));
	}

	vec_grid_vertex_.push_back(RowVector4f(0, 0, f_min, 1));
	vec_grid_vertex_.push_back(RowVector4f(0, 0, f_max, 1));

	vec_grid_vertex_.push_back(RowVector4f(f_min, 0, 0, 1));
	vec_grid_vertex_.push_back(RowVector4f(f_max, 0, 0, 1));

	v_axis_x_text_position_ = RowVector4f(f_min, 0, 0, 1);
	v_axis_z_text_position_ = RowVector4f(0, 0, f_max, 1);

}

void cMainGame::DrawGrid()
{
	Matrix4f mat = mat_view_ * mat_proj_ * mat_viewport_;

	for (size_t i = 0; i < vec_grid_vertex_.size(); i += 2)
	{
		RowVector4f v1 = vec_grid_vertex_[i + 0];
		RowVector4f v2 = vec_grid_vertex_[i + 1];

		v1 = EigenDX::Vector::TransformCoord(v1, mat);
		v2 = EigenDX::Vector::TransformCoord(v2, mat);

		MoveToEx(mem_dc_, v1(0), v1(1), NULL);
		LineTo(mem_dc_, v2(0), v2(1));

	}
}

bool cMainGame::IsBackFace(RowVector4f & v1, RowVector4f & v2, RowVector4f & v3)
{
	RowVector4f v12 = v2 - v1;
	RowVector4f v13 = v3 - v1;
	RowVector3f n = (EigenDX::Vector::Vec4to3(v12)).cross(EigenDX::Vector::Vec4to3(v13));
	RowVector3f l = RowVector3f(0, 0, 1);
	if (n.dot(l) > 0)
		return true;
	else
		return false;
}

void cMainGame::Update_Rotation()
{
	if (GetKeyState('A') & 0x8000)
		box_rot_y_ -= 0.1f;
	if (GetKeyState('D') & 0x8000)
		box_rot_y_ += 0.1f;
}

void cMainGame::Update_Move()
{
	if (GetKeyState('W') & 0x8000)
		v_position_ += v_box_direction_ * 0.1f;
	if (GetKeyState('S') & 0x8000)
		v_position_ -= v_box_direction_ * 0.1f;


}

void cMainGame::Update_Scale()
{
	if (GetKeyState('Z') & 0x8000)
	{
		scale_ += 0.1f;
		if (scale_ > 3.0f)
			scale_ = 3.0f;
	}
	if (GetKeyState('X') & 0x8000)
	{
		scale_ -= 0.1f;
		if (scale_ < 0.1f)
			scale_ = 0.1f;
	}

}

void cMainGame::Update_Old()
{
	RECT rc;
	GetClientRect(_hWnd, &rc);

	v_look_at_ = RowVector4f(0.0f, 0.0f, 0.0f, 1);
	v_eye_ = RowVector4f(0.0f, 5.0f, -5.0f, 1);
	//v_up_ = RowVector4f(0.0f, 5.0f, 5.0f, 1);

	mat_view_ = EigenDX::Matrix::View(v_eye_, v_look_at_, v_up_);
	mat_proj_ = EigenDX::Matrix::Projection(PI / 4.0f, (float)rc.right / rc.bottom,
		1.0f, 1000.0f);

	mat_viewport_ = EigenDX::Matrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render_Old(HDC hdc)
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

		v1 = EigenDX::Vector::TransformCoord(v1, matWVP);
		//v1 = v1 * matWVP;
		v2 = EigenDX::Vector::TransformCoord(v2, matWVP);
		//v2 = v2 * matWVP;
		v3 = EigenDX::Vector::TransformCoord(v3, matWVP);
		//v3 = v3 * matWVP;

		// todo

		v1 = EigenDX::Vector::TransformCoord(v1, mat_viewport_);
		//v1 = v1 * mat_viewport_;
		v2 = EigenDX::Vector::TransformCoord(v2, mat_viewport_);
		//v2 = v2 * mat_viewport_;
		v3 = EigenDX::Vector::TransformCoord(v3, mat_viewport_);
		//v3 = v3 * mat_viewport_;

		MoveToEx(mem_dc_, v1(0), v1(1), NULL);
		LineTo(mem_dc_, v2(0), v2(1));
		LineTo(mem_dc_, v3(0), v3(1));
		LineTo(mem_dc_, v1(0), v1(1));
	}

	DrawGrid();

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, mem_dc_, 0, 0, SRCCOPY);
}