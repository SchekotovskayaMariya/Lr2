#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

template <typename T>
T ChekNum(T min, T max, string h)
{
	T x;
	cout << h;
	while ((cin >> x).fail() || x<min || x>max)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << h;
	}
	return x;
}

struct pipe
{
	int id;
	float length, diameter;
	bool repair_status;
};

struct KC
{
	int id, n_ws, n_ws_op; // n_ws - number of workshops, n_ws_op - number of workshops in operation
	string name;
	float ef; // ef - efficiency
};

pipe CreatePipe()
{
	pipe p;

	p.id = 0;

	p.length = ChekNum(1, 1000, "\nType the length of the pipe: ");

	p.diameter = ChekNum(1, 1000, "\nType the diameter of the pipe: ");

	p.repair_status = ChekNum(0, 1, "\nType the status of the repair pipe (1-under repair, 2-not under repair): ");

	/*cout << "Type the pipe ID: ";

	cout << "\nType the length of the pipe: ";
	cin >> p.length;

	cout << "\nType the diameter of the pipe: ";
	cin >> p.diameter;

	cout << "\nType the status of the repair pipe: ";
	cin >> p.repair_status;*/


	return p;
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

void ViewPipe(const pipe& p)
{
	cout << "\nID: " << p.id << endl
		<< "Length: " << p.length << endl
		<< "Diametr: " << p.diameter << endl
		<< "Repair status: " << p.repair_status << endl;
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

void EditPipe(pipe& p)
{

	if (p.repair_status == 1)
	{
		p.repair_status = 0;
		cout << "\nStatus changed to pipe not under repair\n";
	}
	else
	{
		p.repair_status = 1;
		cout << "\nStatus changed to pipe under repair\n";
	}

}

KC CreateKC()
{
	KC s;

	s.id = 0;

	cout << "\nType a name of the KC: ";
	cin.get();
	getline(cin, s.name);

	s.n_ws = ChekNum(0, 1000, "\nType the number of workshops: ");

	s.n_ws_op = ChekNum(0, s.n_ws, "\nType the number of workshops in operation: ");

	/*cout << "Type the KC ID: ";

	cout << "\nType the number of workshops: ";
	cin >> s.n_ws;

	cout << "\nType the number of workshops in operation: ";
	cin >> s.n_ws_op;

	cout << "\nType the efficiency of the KC: ";
	cin >> s.ef;*/

	srand(time(NULL));
	s.ef = 1. / (rand() % 100);

	return s;
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

void ViewKC(const KC& s)
{
	cout.precision(2);
	cout << "\nID: " << s.id << endl
		<< "Name: " << s.name << endl
		<< "Number of workshops: " << s.n_ws << endl
		<< "Number of workshops in operation: " << s.n_ws_op << endl
		<< "Efficiency: " << s.ef << endl;
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

void EditKC(KC& s)
{
	cout << "\n1. Turn on the workshop ";
	cout << "\n2. Turn off the workshop";
	cout << "\nChoose: ";

	int choiñe;
	choiñe = ChekNum(1, 2, "\Choose again: ");

	if (choiñe == 1 && s.n_ws_op < s.n_ws)
	{

		s.n_ws_op += 1;
		cout << s.n_ws_op;
	}
	else if (choiñe == 0 && s.n_ws_op > 0)
	{
		s.n_ws_op -= 1;
		cout << s.n_ws_op;
	}
	else
	{
		cout << "\nPlease, try again\n";

	}
}

void Menu()
{
	cout << "\nMain menu\n"
		<< "1. Add a pipe\n"
		<< "2. Add a KC\n"
		<< "3. View objects\n"
		<< "4. Edit the pipe\n"
		<< "5. Edit the KC\n"
		<< "6. Save\n"
		<< "7. Upload\n"
		<< "0. Exit\n";
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

void ViewAll(const pipe& p, const KC& s)
{
	cout.precision(2);
	cout << "\nPipe:" << "\nID: " << p.id << endl
		<< "Length: " << p.length << endl
		<< "Diametr: " << p.diameter << endl
		<< "Repair status: " << p.repair_status << endl;
	cout << "\nKC" << "\nID: " << s.id << endl
		<< "Name: " << s.name << endl
		<< "Number of workshops: " << s.n_ws << endl
		<< "Number of workshops in operation: " << s.n_ws_op << endl
		<< "Efficiency: " << s.ef << endl;
}

void ViewThat(const pipe& pi, const KC& st)
{
	switch (ChekNum(1, 3, "\nSelect object 1-Pipe 2-KC 3-All: "))
	{
	case 1:
	{
		ViewPipe(pi);
		break;
	}
	case 2:
	{
		ViewKC(st);
		break;
	}
	case 3:
	{
		ViewAll(pi, st);
		break;
	}
	default:
	{
		cout << "Wrong action" << endl;
	}
	}
}

void UploadThat(pipe& p, KC& s)
{
	switch (ChekNum(1, 3, "\nSelect object 1-Pipe 2-KC 3-All: "))
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
	switch (ChekNum(1, 3, "\nSelect object 1-Pipe 2-KC 3-All: "))
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

istream& operator >>(istream& in, pipe& p)
{
	p.id = 0;

	p.length = ChekNum(1, 1000, "\nType the length of the pipe: ");

	p.diameter = ChekNum(1, 1000, "\nType the diameter of the pipe: ");

	p.repair_status = ChekNum(0, 1, "\nType the status of the repair pipe: ");

	return in;
}

int main()
{
	pipe pi;
	KC st;


	while (true)
	{
		Menu();

		switch (ChekNum(0, 7, "\nSelect the desired number from the menu: "))
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
