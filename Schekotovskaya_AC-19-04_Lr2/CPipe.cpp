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