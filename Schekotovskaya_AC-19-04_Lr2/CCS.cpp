#include "CCS.h"

using namespace std;

int CCS::CountCs = 0;

CCS::CCS()
{
	id = CountCs;
	CountCs++;
}
