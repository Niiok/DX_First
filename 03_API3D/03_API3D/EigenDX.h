#pragma once
#include "Eigen/Eigen"
#include <math.h>
#define _USE_MATH_DEFINES

class EigenDX
{
	class Matrix
	{
	public:
		static Eigen::Matrix4f Translation(float x, float y, float z)
		{
			Eigen::Matrix4f ret;

			ret(3, 0) = x;
			ret(3, 1) = x;
			ret(3, 2) = x;
			ret(3, 3) = 1;

			return ret;
		}

		static Eigen::Matrix4f Translation(Eigen::RowVector4f& v)
		{
			Eigen::Matrix4f ret;

			ret(3, 0) = v(0)/v(3);
			ret(3, 1) = v(1)/v(3);
			ret(3, 2) = v(2)/v(3);
			ret(3, 3) = 1;

			return ret;
		}

		static Eigen::Matrix4f RotationX(float fAngle)
		{
			Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();	
			return ret.eulerAngles(fAngle, 0, 0);
		}

		static Eigen::Matrix4f RotationY(float fAngle);
		static Eigen::Matrix4f RotationZ(float fAngle);
		static Eigen::Matrix4f View(Eigen::RowVector4f& vEye, Eigen::RowVector4f& vLookAt, Eigen::RowVector4f& vUp);
		static Eigen::Matrix4f Projection(float fFovY, float fAspect, float fNearZ, float fFarZ);
		static Eigen::Matrix4f Viewport(float x, float y, float w, float h, float minz, float max);
	};
};

