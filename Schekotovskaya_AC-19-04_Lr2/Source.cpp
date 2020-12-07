#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CCS.h"
#include "CPipe.h"


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

string checkRepair(CPipe& p)
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

void menu()
{
	cout << "1. Add pipe" << endl << "2. Add compressor station" << endl << "3. Show objects" << endl
		<< "4. Edit pipe" << endl << "5. Edit compressor station" << endl << "6. Search by filter" << endl
		<< "7. Delete object" << endl << "8. Save to file" << endl << "9. Download from file" << endl
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
void EditOnePipes(vector<CPipe>& pipes)
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
		EditOnePipes(pipes);
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

pipe UploadPipe()
{
	pipe p;

	ifstream fin;
	fin.open("data1.txt", ios::in);

	if (fin.is_open())
	{
		fin >> p.id;

		fin >> p.length;

		fin >> p.diameter;

		fin >> p.repair_status;

		fin.close();
	}
	return p;
}


void SavePipe(const pipe& p)
{
	ofstream fout;
	fout.open("data1.txt", ios::out);
	if (fout.is_open())
	{
		fout << p.id << endl << p.length << endl << p.diameter << endl << p.repair_status << endl;

		fout.close();
	}
}

void ViewThat(vector<CPipe>& pipes, vector<CCS>& cs)
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
				<< "length: " << p.length << std::endl << "pipe condition: " << checkRepair(p);
		}
		for (CCS c : cs)
		{
			cout.precision(2);// 2 знака после запятой
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
			<< "length: " << pipes[OutPipe].length << endl << "pipe condition: " << checkRepair(pipes[OutPipe]);
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


KC UploadKC()
{
	KC s;

	ifstream fin;
	fin.open("data2.txt", ios::in);

	if (fin.is_open())
	{
		fin >> s.id;

		fin >> s.name;

		fin >> s.n_ws;

		fin >> s.n_ws_op;

		fin >> s.ef;

		fin.close();
	}
	return s;
}


void SaveKC(const KC& s)
{
	ofstream fout;
	fout.open("data2.txt", ios::out);
	if (fout.is_open())
	{
		fout << s.id << endl << s.name << endl << s.n_ws << endl << s.n_ws_op << endl << s.ef << endl;

		fout.close();
	}
}



void SaveAll(const pipe& p, const KC& s)
{
	ofstream fout;
	fout.open("data3.txt", ios::out);

	fout.precision(2);
	fout << p.id << endl
		<< p.length << endl
		<< p.diameter << endl
		<< p.repair_status << endl

		<< s.id << endl
		<< s.name << endl
		<< s.n_ws << endl
		<< s.n_ws_op << endl
		<< s.ef << endl;

	fout.close();
}

void UploadAll(pipe& p, KC& s)
{

	ifstream fin;
	fin.open("data3.txt", ios::in);

	if (fin.is_open())
	{
		fin >> p.id;
		fin >> p.length;
		fin >> p.diameter;
		fin >> p.repair_status;

		fin >> s.id;
		fin >> s.name;
		fin >> s.n_ws;
		fin >> s.n_ws_op;
		fin >> s.ef;


	}
	fin.close();
}




void UploadThat(pipe& p, KC& s)
{
	switch (ChekNum(1, 3)
	{
	case 1:
	{
		ViewPipe(UploadPipe());
		break;
	}
	case 2:
	{
		ViewKC(UploadKC());
		break;
	}
	case 3:
	{
		UploadAll(p, s);
		break;
	}
	default:
	{
		cout << "Wrong action" << endl;
	}
	}
}

void SaveThat(const pipe& pi, const KC& st)
{
	switch (ChekNum(1, 3))
	{
	case 1:
	{
		SavePipe(pi);
		break;
	}
	case 2:
	{
		SaveKC(st);
		break;
	}
	case 3:
	{
		SaveAll(pi, st);
		break;
	}
	default:
	{
		cout << "Wrong action" << endl;
	}
	}
}


int main()
{
	pipe pi;
	KC st;


	while (true)
	{
		Menu();

		switch (ChekNum(0, 7))
		{
		case 1:
		{	cin >> pi;
		break;
		}
		case 2:
		{
			st = CreateKC();
			break;
		}
		case 3:
		{
			ViewThat(pi, st);
			break;
		}
		case 4:
		{
			EditPipe(pi);
			break;
		}
		case 5:
		{
			EditKC(st);
			break;
		}
		case 6:
		{
			SaveThat(pi, st);
			break;
		}
		case 7:
		{
			UploadThat(pi, st);
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
