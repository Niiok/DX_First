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
	//vector<RowVector4f>	vec_line_vertex_;

	Matrix4f			mat_world_;
	Matrix4f			mat_view_;
	Matrix4f			mat_proj_;
	Matrix4f			mat_viewport_;

	RowVector4f			v_eye_;
	RowVector4f			v_look_at_;
	RowVector4f			v_up_;

	// transform
	RowVector4f			v_position_;
	float				box_rot_y_;
	RowVector4f			v_box_direction_;

	//grid
	vector<RowVector4f>	vec_grid_vertex_;
	RowVector4f			v_axis_x_text_position_;
	RowVector4f			v_axis_z_text_position_;

	// camera
	POINT				pt_prev_mouse_;
	bool				is_l_button_down_;
	float				camera_distance_;
	RowVector4f			v_cam_rot_angle_;
	
	float				scale_;

public :
	void SetUp();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetGrid();
	void DrawGrid();

	bool IsBackFace(RowVector4f& v1, RowVector4f& v2, RowVector4f& v3);

	void Update_Rotation();
	void Update_Move();
	void Update_Scale();

	void Update_Old();
	void Render_Old(HDC hdc);
};

