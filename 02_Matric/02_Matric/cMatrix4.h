#pragma once
#include <vector>

class cMatrix4
{
public:
	cMatrix4();
	~cMatrix4();

private:
	class cRow
	{
	private:
		std::vector<float> vecData;
	public:
		cRow();
		cRow(int nDimension);
		~cRow() {}
		void Resize(int nDimension);
		float& operator[] (int nIndex);
	};

	std::vector<cRow> vecData;

public:
	cMatrix4(int nDimension);
	void Print();
	void Resize(int nDimension);
	int Dimension();

};

