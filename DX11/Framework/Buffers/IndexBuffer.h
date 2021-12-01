#pragma once
class IndexBuffer
{
public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

private:
	ID3D11Buffer* buffer;

	void* data;
	UINT count;

	bool bGpuWrite;
	bool bCpuWrite;

public:
	UINT Count() { return count; }
	ID3D11Buffer* buffer() { return buffer; }

	void Render();

};

