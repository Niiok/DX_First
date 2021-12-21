#pragma once

#include "Systems//IExecute.h"

class MeshDemo : public IExecute
{
	virtual void Initialize() override;
	virtual void Ready() override {};
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

private:
	Shader* shader;

	// material
	Material* floor;
	Material* stone;
	Material* brick;
	Material* wall;

	//Mesh
	MeshSphere* sphere[10];
	MeshCylinder* cylinder[10];

	MeshCube* cube;
	MeshGrid* grid;

	Model* model;
	ModelRender* modelRender;
};