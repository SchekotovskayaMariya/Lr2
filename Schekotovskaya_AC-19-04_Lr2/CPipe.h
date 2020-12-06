#pragma once
class CPipe
{
#pragma once
#include <iostream>
#include <string>


	class CPipe
	{
	public:
		int id;
		static int CountP;
		float diametr, length;
		bool repair = false;
		friend std::string checkRepair(const CPipe& p);
		CPipe();
	};
};

