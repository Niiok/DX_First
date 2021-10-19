#pragma once
#include "Eigen/Eigen"
#include <math.h>
#define _USE_MATH_DEFINES

namespace EigenDX
{
	class Vector
	{
	public:

		/*static RowVector4f Cross(RowVector4f& v1, RowVector4f& v2)
		{
			if (v1(3) != 0)
			{
				v1(0) /= v1(3);
				v1(1) /= v1(3);
				v1(2) /= v1(3);
				v1(3) = 1;
			}
			if (v2(3) != 0)
			{
				v2(0) /= v2(3);
				v2(1) /= v2(3);
				v2(2) /= v2(3);
				v2(3) = 1;
			}

			RowVector4f v;
			v(0) = v1(1) * v2(2) - v1(2) * v2(1);
			v(1) = v1(2) * v2(0) - v1(0) * v2(2);
			v(2) = v1(0) * v2(1) - v1(1) * v2(0);
			return v;
		}*/

		static Eigen::RowVector3f	Vec4to3(Eigen::RowVector4f& v)
		{
			Eigen::RowVector3f ret;
			ret(0) = v(0);
			ret(1) = v(1);
			ret(2) = v(2);

			if (v(3) != 0 && v(3) != 1)
			{
				ret(0) /= v(3);
				ret(1) /= v(3);
				ret(2) /= v(3);
			}

			return ret;
		}
		static Eigen::RowVector4f	Vec3to4(Eigen::RowVector3f& v)
		{
			Eigen::RowVector4f ret;
			ret(0) = v(0);
			ret(1) = v(1);
			ret(2) = v(2);
			ret(3) = 1;

			return ret;
		}

		static Eigen::RowVector4f	TransformCoord(Eigen::RowVector4f& v, Eigen::Matrix4f& mat) // : point
		{
			Eigen::RowVector4f vRet;
			vRet(0) = v(0) * mat(0, 0) + v(1) * mat(1, 0) + v(2) * mat(2, 0) + 1.0f * mat(3, 0);
			vRet(1) = v(0) * mat(0, 1) + v(1) * mat(1, 1) + v(2) * mat(2, 1) + 1.0f * mat(3, 1);
			vRet(2) = v(0) * mat(0, 2) + v(1) * mat(1, 2) + v(2) * mat(2, 2) + 1.0f * mat(3, 2);
			vRet(3) = v(0) * mat(0, 3) + v(1) * mat(1, 3) + v(2) * mat(2, 3) + 1.0f * mat(3, 3);

			if (vRet(3) < -FLT_EPSILON || vRet(3) > FLT_EPSILON)
			{
				vRet(0) /= vRet(3);
				vRet(1) /= vRet(3);
				vRet(2) /= vRet(3);
				vRet(3) /= vRet(3);
			}

			return vRet;
		}
		static Eigen::RowVector4f	TransformNormal(Eigen::RowVector4f& v, Eigen::Matrix4f& mat) // : vector
		{
			Eigen::RowVector4f	vRet;
			vRet(0) = v(0) * mat(0, 0) + v(1) * mat(1, 0) + v(2) * mat(2, 0);
			vRet(1) = v(0) * mat(0, 1) + v(1) * mat(1, 1) + v(2) * mat(2, 1);
			vRet(2) = v(0) * mat(0, 2) + v(1) * mat(1, 2) + v(2) * mat(2, 2);
			vRet(3) = 0;

			return vRet;
		}
	};

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

			if (v(3) == 0)
				return ret;

			ret(3, 0) = v(0)/v(3);
			ret(3, 1) = v(1)/v(3);
			ret(3, 2) = v(2)/v(3);
			ret(3, 3) = 1;

			return ret;
		}

		static Eigen::Matrix4f RotationX(float fAngle)
		{
			Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();	
			ret(1, 1) = cosf(fAngle);
			ret(1, 2) = sinf(fAngle);
			ret(2, 1) = -sinf(fAngle);
			ret(2, 2) = cosf(fAngle);
			return ret;
		}
		static Eigen::Matrix4f RotationY(float fAngle)
		{
			Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();
			ret(0, 0) = cosf(fAngle);
			ret(0, 2) = -sinf(fAngle);
			ret(2, 0) = sinf(fAngle);
			ret(2, 2) = cosf(fAngle);
			return ret;
		}
		static Eigen::Matrix4f RotationZ(float fAngle)
		{
			Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();
			ret(0, 0) = cosf(fAngle);
			ret(0, 1) = sinf(fAngle);
			ret(1, 0) = -sinf(fAngle);
			ret(1, 1) = cosf(fAngle);
			return ret;
		}
		static Eigen::Matrix4f View(Eigen::RowVector4f& vEye, Eigen::RowVector4f& vLookAt, Eigen::RowVector4f& vUp)
		{
			Eigen::RowVector3f l = (Vector::Vec4to3(vLookAt) - Vector::Vec4to3(vEye)).normalized();
			Eigen::RowVector3f r = Vector::Vec4to3(vUp).cross(l).normalized();
			Eigen::RowVector3f u = l.cross(r).normalized();

			Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();
			ret(0, 0) = r(0);  ret(0, 1) = u(0); ret(0, 2) = l(0);
			ret(1, 0) = r(1);  ret(1, 1) = u(1); ret(1, 2) = l(1);
			ret(2, 0) = r(2);  ret(2, 1) = u(2); ret(2, 2) = l(2);

			ret(3, 0) = -r.dot(Vector::Vec4to3(vEye));
			ret(3, 1) = -u.dot(Vector::Vec4to3(vEye));
			ret(3, 2) = -l.dot(Vector::Vec4to3(vEye));

			return ret;
		}
		static Eigen::Matrix4f Projection(float fFovY, float fAspect, float fNearZ, float fFarZ)
		{
			Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();

			float fScaleY = 1.0f / tanf(fFovY / 2.0f);
			float fScaleX = fScaleY / fAspect;

			ret(0, 0) = fScaleX;
			ret(1, 1) = fScaleY;
			ret(2, 2) = fFarZ / (fFarZ - fNearZ);
			ret(2, 3) = 1.0f;
			ret(3, 2) = -fFarZ * fNearZ / (fFarZ - fNearZ);
			ret(3, 3) = 0.0f;

			return ret;
		}
		static Eigen::Matrix4f Viewport(float x, float y, float w, float h, float minz, float maxz)
		{
			Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();
			ret(0, 0) = w / 2.0f;
			ret(1, 1) = -h / 2.0f;
			ret(2, 2) = maxz - minz;
			ret(3, 0) = x + w / 2.0f;
			ret(3, 1) = y + h / 2.0f;
			ret(3, 2) = minz;
			return ret;
		}
		static Eigen::Matrix4f Scale(float scale)
		{
			Eigen::Matrix4f ret = Eigen::Matrix4f::Identity();
			ret(0, 0) = scale;
			ret(1, 1) = scale;
			ret(2, 2) = scale;

			return ret;
		}
	};



};

