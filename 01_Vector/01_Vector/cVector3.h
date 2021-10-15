#pragma once
#include "global.h"

class cVector3
{
public:
	cVector3();
	cVector3(float x, float y, float z);
	~cVector3();

	float x, y, z;

	void Print();
	//string ToString();

	bool operator==(cVector3& vec);
	bool operator!=(cVector3& vec);
	cVector3 operator+(cVector3& vec);
	cVector3 operator-(cVector3& vec);
	cVector3 operator*(float f);
	cVector3 operator/(float f);
	static float Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);
	float Length();
	cVector3 Normal();
};

