#include "CCS.h"

using namespace std;

int CCS::CountCs = 0;

CCS::CCS()
{
	id = CountCs;
	CountCs++;
}

int CCS::GetId()
{
	return id;
}

void CCS::SetId(int& id)
{
	this->id = id;
}
