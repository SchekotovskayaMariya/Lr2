#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CCS.h"
#include "CPipe.h"
#include <unordered_map>

using namespace std;

template <typename T>
T CheckNum(T min, T max)
{
	T x;
	while ((cin >> x).fail() || x < min || x > max)
	{
		cout << "Please enter a valid value - ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return x;
}

string WordRepair(CPipe& p)
{
	if (p.repair)
	{
		return "Unworking \n\n";
	}
	else
	{
		return "Working \n\n";
	}
}

istream& operator>>(std::istream& in, CCS& cs)
{
	cout << "Enter the name of the compressor station - ";
	cin.ignore();
	getline(cin, cs.name);

	cout << "Enter the number of workshops - ";
	cs.totalShop = CheckNum(0, 1000);
	cout << "Enter the number of workshop workers - ";
	cs.workShop = CheckNum(0, cs.totalShop);

	cs.efficiency = 1. / (rand() % 10);
	cout << endl;
	return in;
}

istream& operator>> (std::istream& in, CPipe& p)
{
	cout << "\nEnter the diameter in millimeters - ";
	p.diametr = CheckNum<float>(0, 10000);
	cout << "Enter the length in meters - ";
	p.length = CheckNum<float>(0, 10000);
	cout << endl;
	return in;
}

void Menu()
{
	cout << "1. Add pipe" << endl << "2. Add compressor station" << endl << "3. Show objects" << endl
		<< "4. Edit pipe" << endl << "5. Edit compressor station" << endl << "6. Search by filter" << endl
		<< "7. Delete object" << endl << "8. Save to file" << endl << "9. Download from file" << endl << "10. Topological sort" << endl
		<< "0. Exit" << endl << endl << "Selected action - ";
}

void EditAllPipes(vector<CPipe>& pipes)
{
	cout << "0. Pipes working\n1. Pipes in repair\nChoose - ";
	int choice = CheckNum(0, 1);
	cout << endl;
	for (CPipe& i : pipes)
	{
		i.repair = choice;
	}
}
void EditOnePipe(vector<CPipe>& pipes)
{
	cout << "Select id you want to edit: ";
	int k;
	cin >> k;
	cout << "0. Pipe working\n1. Pipe in repair\nChoose - ";
	int choice = CheckNum(0, 1);
	pipes[k].repair = choice;
	cout << endl;
}
void EditPipe(vector<CPipe>& pipes)
{
	cout << "1. Edit all existing ones\n2. Edit one pipe\nSelect - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << endl;
		EditAllPipes(pipes);
	}
	else
	{
		cout << endl;
		EditOnePipe(pipes);
	}
}

void EditAllCs(vector<CCS>& cs)
{
	cout << "\n0. Start the workshop\n1. Stop the workshop\nSelect - ";
	int choice = CheckNum(0, 1);
	cout << endl;
	for (CCS& i : cs)
	{
		if (choice == 0)
		{
			i.workShop += 1;
		}
		else if (i.workShop > 0)
		{
			i.workShop -= 1;
		}
	}
}
void EditOneCs(vector<CCS>& cs)
{
	cout << "Id of the compressor station you want to edit: ";
	int k;
	cin >> k;
	cout << "\n0. Start the workshop\n1. Stop the workshop\nSelect - ";
	if (CheckNum(0, 1) == 0)
	{
		cs[k].workShop += 1;
	}
	else
	{
		if (cs[k].workShop > 0)
			cs[k].workShop -= 1;
	}
}

void EditCs(vector<CCS>& cs)
{
	cout << "1. Edit all existing ones\n2. Edit one cs\nSelect - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << endl;
		EditAllCs(cs);
	}
	else
	{
		cout << endl;
		EditOneCs(cs);
	}
}


void ViewObjects(vector<CPipe>& pipes, vector<CCS>& cs)
{
	cout << "1. View all\n" << "2. View pipes\n" << "3. View compressor stations\nSelect - ";
	switch (CheckNum(1, 3))
	{
	case 1:
	{
		cout << endl;
		for (CPipe p : pipes)
		{
			cout << "Pipe id: " << p.id << std::endl << "diametr: " << p.diametr << std::endl
				<< "length: " << p.length << std::endl << "pipe condition: " << WordRepair(p);
		}
		for (CCS c : cs)
		{
			cout.precision(2);
			cout << "\nCS id: " << c.id << endl << "Name: " << c.name
				<< endl << "Quantity of workshops: " << c.totalShop << endl
				<< "Quantity of workshop workers: " << c.workShop << endl
				<< "Efficiency: " << c.efficiency << endl << endl;
		}
		break;
	}
	case 2:
	{
		cout << "Select id you want to output: ";
		int OutPipe;
		cin >> OutPipe;
		cout << "Pipe id: " << pipes[OutPipe].id << endl << "diametr: " << pipes[OutPipe].diametr << endl
			<< "length: " << pipes[OutPipe].length << endl << "pipe condition: " << WordRepair(pipes[OutPipe]);
		break;
	}
	case 3:
	{
		cout << "Select id you want to output: ";
		int OutCs;
		cin >> OutCs;
		cout.precision(2);
		cout << "\nCS id: " << cs[OutCs].id << endl << "Name: " << cs[OutCs].name
			<< endl << "Quantity of workshops: " << cs[OutCs].totalShop << endl
			<< "Quantity of workshop workers: " << cs[OutCs].workShop << endl
			<< "Efficiency: " << cs[OutCs].efficiency << endl << endl;;
		break;
	}
	}
}


void SaveAll(vector<CPipe>& pipes, vector<CCS>& cs)
{
	ofstream fout;
	string name;
	cout << "Enter name file: ";
	cin.ignore();
	getline(cin, name);
	fout.open(name, ios::out);
	if (fout.is_open())
	{
		fout << pipes.size() << endl;
		fout << cs.size() << endl;
		fout << endl;

		for (CPipe p : pipes)
		{
			fout << p.id << endl << p.diametr << endl
				<< p.length << endl << p.repair << endl << endl;
		}
		for (CCS i : cs)
		{
			fout.precision(2);
			fout << i.id << endl << i.name << endl << i.totalShop << endl
				<< i.workShop << endl << i.efficiency << endl << endl;
		}
		cout << "Saved\n\n";
		fout.close();
	}
}

void UploadAll(vector<CPipe>& pipes, vector<CCS>& cs)
{
	ifstream fin;
	string name;
	cout << "Enter name file: ";
	cin.ignore();
	getline(cin, name);
	fin.open(name, ios::in);
	if (fin.is_open())
	{
		int lenpipe, lencs;
		fin >> lenpipe;
		fin >> lencs;
		pipes.resize(lenpipe);
		cs.resize(lencs);
		int id;
		for (CPipe& p : pipes)
		{
			fin >> p.id;
			fin >> p.diametr;
			fin >> p.length;
			fin >> p.repair;
		}
		for (CCS& c : cs)
		{
			fin >> c.id;
			fin >> c.name;
			fin >> c.totalShop;
			fin >> c.workShop;
			fin >> c.efficiency;
		}
		fin.close();
		cout << "Data downloaded\n\n";
	}
}

bool SearchById(CPipe& p, int param)
{
	return p.id == param;
}

bool SearchByRepair(CPipe& p, int param)
{
	return p.repair == param - 1;
}

bool SearchByName(CCS& cs, string name)
{
	return cs.name == name;
}

bool SearchByPercent(CCS& cs, int param)
{
	return 100 * (1 - (1. * cs.workShop) / cs.totalShop) >= param;
}

template <typename N>
void ForFilterPipes(vector<CPipe>& pipes, bool(*f)(CPipe& p, N param), N param)
{
	for (CPipe& i : pipes)
	{
		if (f(i, param))
		{
			cout << endl << "Pipe id: " << i.id << std::endl << "diametr: " << i.diametr << std::endl
				<< "length: " << i.length << std::endl << "pipe condition: " << WordRepair(i);
		}
	}
	cout << endl;
}
template <typename N>
void ForFilterCs(vector<CCS>& cs, bool(*f)(CCS& p, N param), N param)
{
	for (CCS& i : cs)
	{
		if (f(i, param))
		{
			cout.precision(2);
			cout << "\nCS id: " << i.id << endl << "Name: " << i.name
				<< endl << "Quantity of workshops: " << i.totalShop << endl
				<< "Quantity of workshop workers: " << i.workShop << endl
				<< "Efficiency: " << i.efficiency << endl << endl;
		}
	}
	cout << endl;
}

void SearchByFilterPipes(vector<CPipe>& pipes)
{
	cout << "\n1. By ID\n2. By condition\nSelect action - ";
	if (CheckNum(1, 2) == 1)
	{
		cout << "Enter ID: ";
		int ch = CheckNum(0, 100);
		ForFilterPipes(pipes, SearchById, ch);
	}
	else
	{
		cout << "\n1. Working\n2. Unworking\nSelect action - ";
		int choice = CheckNum(1, 2);
		ForFilterPipes(pipes, SearchByRepair, choice);
	}
}
void SearchByFilterCs(vector<CCS>& cs)
{
	cout << "\n1. By name\n" << "2. By percentage of unused workshops\nSelect action - ";
	if (CheckNum(1, 2) == 1)
	{
		int counter = 0;
		cout << "\nEnter a name from this list: ";
		string name;
		cin >> name;
		ForFilterCs(cs, SearchByName, name);
	}
	else
	{
		cout << "\nEnter the number of percentages - ";
		int choice = CheckNum(0, 100);
		ForFilterCs(cs, SearchByPercent, choice);
	}
}

void DeleteObject(vector <CPipe>& pipes, vector <CCS>& cs)
{
	cout << "1. Delete pipe\n2. Delete compressor station\nSelect action - ";
	int choice = CheckNum(1, 2);
	if (choice == 1)
	{
		cout << "Enter ID: ";
		int ch = CheckNum(0, 100);
		pipes.erase(pipes.begin() + ch);
		cout << endl;
	}
	else
	{
		cout << "Enter ID: ";
		int ch = CheckNum(0, 100);
		cs.erase(cs.begin() + ch);
		cout << endl;
	}
}

int main()
{
	vector <CPipe> pipes;
	vector <CCS> cs;

	while (true)
	{
		Menu();

		switch (CheckNum(0, 10))
		{
		case 1:
		{
			CPipe p;
			cin >> p;
			pipes.push_back(p);
			break;
		}
		case 2:
		{
			CCS c;
			cin >> c;
			cs.push_back(c);
			break;
		}
		case 3:
		{
			ViewObjects(pipes, cs);
			break;
		}
		case 4:
		{
			EditPipe(pipes);
			break;
		}
		case 5:
		{
			EditCs(cs);
			break;
		}
		case 6:
		{
			cout << "1. Search by pipes\n2. Search by compressor stations\nSelect action - ";
			if (CheckNum(1, 2) == 1)
				SearchByFilterPipes(pipes);
			else
				SearchByFilterCs(cs);
			break;
		}
		case 7:
		{
			DeleteObject(pipes, cs);
			break;
		}
		case 8:
		{
			SaveAll(pipes, cs);
			break;
		}
		case 9:
		{
			UploadAll(pipes, cs);
			break;
		}
		case 10:
		{

			break;
		}
		case 0:
		{
			return 0;
		}
		default:
		{
			cout << "Wrong action" << endl;
		}
		}
	}
	return 0;

}
