#include "Framework.h"
#include "Camera.h"


Camera::Camera()
	: position(5, 5, 10)
	, forward(0, 0, 1)
	, right(1, 0, 0)
	, up(0, 1, 0)
	, rotation(0, 0, 0)
{
	D3DXMatrixIdentity(&matRotation);
	Rotation();

	D3DXMatrixIdentity(&matView);
	Move();
}

Camera::~Camera()
{
}

void Camera::Position(float x, float y, float z)
{
	Position(Vector3(x, y, z));
}

void Camera::Position(Vector3 & vec)
{
	position = vec;
	Move();
}

void Camera::Position(Vector3 * vec)
{
	//position = *vec;
	*vec = position;
}

void Camera::GetMatrix(Matrix * matrix)
{
	memcpy(matrix, &matView, sizeof(Matrix));
}

void Camera::Rotation(float x, float y, float z)
{
	Rotation(Vector3(x, y, z));
}

void Camera::Rotation(Vector3 & vec)
{
	rotation = vec;
	Rotation();
}

void Camera::Rotation(Vector3 * vec)
{
	//rotation = *vec;
	*vec = rotation;
}

void Camera::RotationDegree(float x, float y, float z)
{
	RotationDegree(Vector3(x, y, z));
}

void Camera::RotationDegree(Vector3 & vec)
{
	//rotation = vec * Math::PI / 180.0f;
	rotation = vec * 0.01745329f;
	Rotation();
}

void Camera::RotationDegree(Vector3 * vec)
{
	//*vec = rotation * 180.0f / Math::PI;
	*vec = rotation * 57.2957951f;
}

void Camera::View()
{
	D3DXMatrixLookAtLH(&matView, &position, &(position + forward), &up);
}

void Camera::Move()
{
	View();
}

void Camera::Rotation()
{
	Matrix X, Y, Z;
	D3DXMatrixRotationX(&X, rotation.x);
	D3DXMatrixRotationY(&Y, rotation.y);
	D3DXMatrixRotationZ(&X, rotation.z);
	//D3DXMatrixRotationYawPitchRoll();

	matRotation = X * Y * Z;

	D3DXVec3TransformNormal(&forward, &Vector3(0, 0, 1), &matRotation);
	D3DXVec3TransformNormal(&right, &Vector3(1, 0, 0), &matRotation);
	D3DXVec3TransformNormal(&up, &Vector3(0, 1, 0), &matRotation);
}
