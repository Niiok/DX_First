#include "framework.h"
#include "cCamera.h"

cCamera::cCamera()
	: m_vCameraRotAngle(0,0,0)
	, m_vEye(0,0,-5)
	, m_vLookAt(0,0,0)
	, m_vUp(0,1,0)
	, m_pvTarget(NULL)
	, m_fCameraDistance(5.0f)
	, m_isLButtonDown(false)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}

cCamera::~cCamera()
{
}

void cCamera::Setup(D3DXVECTOR3 * pvTarget)
{
	m_pvTarget = pvTarget;

	// lost

}

void cCamera::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCameraRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCameraRotAngle.y);
	matR = matRX * matRY;

	m_vEye = D3DXVECTOR3(0, 0, -m_fCameraDistance);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	if (m_pvTarget)
	{
		m_vLookAt = *m_pvTarget;
		m_vEye += *m_pvTarget;
	}

	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f,
		rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	// lost?
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
		break;

	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;

	case WM_MOUSEMOVE:
		if (m_isLButtonDown)
		{
			POINT pt_cur_mouse;
			pt_cur_mouse.x = LOWORD(lParam);
			pt_cur_mouse.y = HIWORD(lParam);
			float delta_x = (float)pt_cur_mouse.x - m_ptPrevMouse.x;
			float delta_y = (float)pt_cur_mouse.y - m_ptPrevMouse.y;

			m_vCameraRotAngle.y += (delta_x / 100.0f);
			m_vCameraRotAngle.x -= (delta_y / 100.0f);

			if (m_vCameraRotAngle.x < -D3DX_PI / 2.0f + 0.0001f)
				m_vCameraRotAngle.x = -D3DX_PI / 2.0f + 0.0001f;
			if (m_vCameraRotAngle.x < D3DX_PI / 2.0f + 0.0001f)
				m_vCameraRotAngle.x = D3DX_PI / 2.0f + 0.0001f;

			m_ptPrevMouse = pt_cur_mouse;
		}
		break;

	case WM_MOUSEWHEEL:
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.0f);
		if (m_fCameraDistance < 0.000f)
			m_fCameraDistance = 0.0001f;
		break;

	default:
		break;
	}
}
