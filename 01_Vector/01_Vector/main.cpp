#include "global.h"
#include "cVector3.h"

int main()
{
	cVector3 vec1(1.0f, 0.0f, 0.0f);
	cVector3 vec2(0.0f, 1.0f, 0.0f);

	cout << "vec1 == vec2 : " << (vec1 == vec2) << "\n";
	cout << "vec1 != vec2 : " << (vec1 != vec2) << "\n";

	cVector3 vec3 = vec1 + vec2;

	printf("vec1 + vec2 : (%f, %f, %f)\n", vec3.x, vec3.y, vec3.z);

	cVector3 vec4 = vec1 - vec2;

	printf("vec1 - vec2 : (%f, %f, %f)\n", vec4.x, vec4.y, vec4.z);

	cVector vec5 = 
}