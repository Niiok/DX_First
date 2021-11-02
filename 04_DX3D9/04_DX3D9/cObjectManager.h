#pragma once

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
private:
	Singletone(cObjectManager);

private:
	std::set<cObject*> m_setObject;

public:
	void AddObject(cObject* pObject)
	{
		m_setObject.insert(pObject);
	}

	void RemoveObject(cObject* pObject)
	{
		m_setObject.erase(pObject);
	}


};

