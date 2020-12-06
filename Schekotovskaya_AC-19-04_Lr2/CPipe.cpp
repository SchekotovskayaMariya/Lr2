#include "CPipe.h"
#include <iostream>
#include <string>

using namespace std;

int CPipe::CountP = 0;

CPipe::CPipe()
{
	id = CountP++;
}


std::string checkRepair(const CPipe& p)//rename and class
{
	return (p.repair) ? "Unworking \n\n" : "Working \n\n";

}
