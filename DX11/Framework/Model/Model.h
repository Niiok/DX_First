#pragma once
#define MAX_MODEL_TRANSFORM 128

class ModelBone;
class ModelMeshPart;
class ModelMesh;

class Model
{
public:
	Model();
	~Model();

	typedef VertexTextureNormal ModelVertex;

private:
	vector<Material*> materials;

public:
	UINT MaterialCount() { return materials.size(); }
};

