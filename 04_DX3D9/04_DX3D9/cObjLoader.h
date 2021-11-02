#pragma once

class cMtlTex;
class cGroup;

class cObjLoader
{
public:
	cObjLoader();
	~cObjLoader();

private:
	std::map<std::string, cMtlTex*> m_mapMtlTex;

public:
	void Load(OUT std::vector<cGroup*>& vecGroup,
		IN const char* szFolder, IN const char* szFile);
	void LoadMtlLib(const char* szFolder, const char* szFile);
};

