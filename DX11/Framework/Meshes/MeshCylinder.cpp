#include  "Framework.h"
#include "MeshCylinder.h"


void MeshCylinder::BuildTopCap()
{
	/*float y = 0.5f * height;
	float theta = 2.0f * Math::PI / (float)sliceCount;

	for (UINT i = 0; i <= sliceCount; i++)
	{
		float x = topRadius * cosf(i*theta);
		float z = topRadius * sinf(i*theta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertices.push_back(MeshVertex(x, y, z, 0, 1, 0));
	}
	vertices.push_back(MeshVertex(0, y, 0, 0, 1, 0));

	UINT baseIndex = vertices.size() - sliceCount - 2;
	UINT centerIndex = vertices.size() - 1;

	for (UINT i - 0; i < sliceCount; i++)
	{
		indeices.push_back(centerIndex);
		indeices.push_back(baseIndex + i +1);
		indeices.push_back(baseIndex + i);
	}*/


}

void MeshCylinder::BuildBottomCap()
{
	/*float y = -0.5f * height;
	float theta = 2.0f * Math::PI / (float)sliceCount;

	for (UINT i = 0; i <= sliceCount; i++)
	{
		float x = topRadius * cosf(i*theta);
		float z = topRadius * sinf(i*theta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		vertices.push_back(MeshVertex(x, y, z, 0, -1, 0));
	}
	vertices.push_back(MeshVertex(0, y, 0, 0, -1, 0));

	UINT baseIndex = vertices.size() - sliceCount - 2;
	UINT centerIndex = vertices.size() - 1;

	for (UINT i - 0; i < sliceCount; i++)
	{
		indeices.push_back(centerIndex);
		indeices.push_back(baseIndex + i);
		indeices.push_back(baseIndex + i + 1);
	}*/
}
