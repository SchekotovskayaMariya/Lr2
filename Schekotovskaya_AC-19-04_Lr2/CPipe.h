#pragma once
#include <iostream>
#include <string>


	class CPipe
	{
	private:
		int id;

	public:
		static int CountP;
		float diametr, length;
		bool repair = false;
		CPipe();
		int GetId();
		void SetId(int& id);
	};