#pragma once
class BillboardDemo : public IExecute
{
public:
	BillboardDemo();
	~BillboardDemo();


	// IExecute을(를) 통해 상속됨
	virtual void Initialize() override;

	virtual void Ready() override {}

	virtual void Destroy() override {}

	virtual void Update() override;

	virtual void PreRender() override {}

	virtual void Render() override;

	virtual void PostRender() override {}

	virtual void ResizeScreen() override {}


private:
	class Billboard* billboard;
	class Sky* sky;

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

