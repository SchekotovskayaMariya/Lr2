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
		CPipe();
	};