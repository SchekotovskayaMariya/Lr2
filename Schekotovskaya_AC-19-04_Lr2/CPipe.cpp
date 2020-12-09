#include "CPipe.h"
#include <iostream>
#include <string>

using namespace std;

int CPipe::CountP = 0;

CPipe::CPipe()
{
	id = CountP;
	CountP++;
}

int CPipe::GetId()
{
	return id;
}

void CPipe::SetId(int& id)
{
	this->id = id;
}
