#pragma once
#include <iostream>
#include <string>

using namespace std;

class CCS
{
private:
	int id;
public:
	static int CountCs;
	int totalShop, workShop;
	float efficiency;
	string name;
	CCS();
	int GetId();
	void SetId(int& id);
};