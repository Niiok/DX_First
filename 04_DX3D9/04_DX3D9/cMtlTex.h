#pragma once
#include "cObject.h"
class cMtlTex :
	public cObject
{
	cMtlTex();
	~cMtlTex();

private:
	Synthesize(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	Synthesize(D3DMATERIAL9, m_pMaterial, Material);


};

