#pragma once
#include "Mesh.h"
class MeshSphere
	: public Mesh
{
public:
	MeshSphere(Shader* shader, float radius, UINT sliceCount);
	virtual ~MeshSphere();

	void Create() override;
};

