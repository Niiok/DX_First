#include "cVector3.h"

cVector3::cVector3()
{
}

cVector3::cVector3(float _x, float _y, float _z)
	:x(_x), y(_y), z(_z)
{
}

cVector3::~cVector3()
{
}

void cVector3::Print()
{
	printf("Vector : ( %8,2f, %8.2f, %8.2f )\n", x, y, z);
}

//string cVector3::ToString()
//{
//	string("%f, %f, %f", x, y, z);
//}

bool cVector3::operator==(cVector3 & vec)
{
	if (x - FLT_EPSILON <= vec.x && vec.x <= x + FLT_EPSILON &&
		y - FLT_EPSILON <= vec.y && vec.y <= y + FLT_EPSILON &&
		z - FLT_EPSILON <= vec.z && vec.z <= z + FLT_EPSILON)
		return true;
	else
		return false;
}

bool cVector3::operator!=(cVector3 & vec)
{
	return !operator==(vec);
}

cVector3 cVector3::operator+(cVector3 & vec)
{
	cVector3 v;
	v.x = x + vec.x;
	v.y = y + vec.y;
	v.z = z + vec.z;

	return v;
}

cVector3 cVector3::operator-(cVector3 & vec)
{
	cVector3 v;
	v.x = x - vec.x;
	v.y = y - vec.y;
	v.z = z - vec.z;

	return v;
}

cVector3 cVector3::operator*(float f)
{
	cVector3 v;
	v.x = x * f;
	v.y = y * f;
	v.z = z * f;

	return v;
}

cVector3 cVector3::operator/(float f)
{
	cVector3 v;
	v.x = x / f;
	v.y = y / f;
	v.z = z / f;

	return v;
}

float cVector3::Dot(cVector3 & v1, cVector3 & v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

cVector3 cVector3::Cross(cVector3 & v1, cVector3 & v2)
{
	cVector3 v;
	v.x = v1.y*v2.z - v1.z*v2.y;
	v.y = v1.z*v2.x - v1.x*v2.z;
	v.z = v1.x*v2.y - v1.y*v2.x;

	return v;
}

float cVector3::Length()
{
	return (float)sqrt(x * x + y * y + z * z);
}

cVector3 cVector3::Normal()
{
	float len = Length();
	cVector3 v;

	v.x = x / len;
	v.y = y / len;
	v.z = z / len;

	return v;
}
