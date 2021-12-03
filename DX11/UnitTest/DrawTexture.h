#pragma once

#include "Systems//IExecute.h"

class DrawTexture : public IExecute
{
public:
		// IExecute을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Ready() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void ResizeScreen() override;

private:
	Shader* shader;

	UINT width = 400;
	UINT height = 400;

	UINT vertexCount = 4;
	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount = 6;
	UINT* indices;
	ID3D11Buffer* indexBuffer;

	//Color Color;
	ID3D11ShaderResourceView* srv;
	Texture* texture;

	UINT number;
};

