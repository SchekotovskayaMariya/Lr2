#include "GazTransNet.h"
#include "Utils.h"
using namespace std;

void GazTransNet::ViewAllReadyPipe(const unordered_map<int, CPipe>& pipes)
{
	bool is_first = true;
	for (const auto& i : pipes)
	{
		if ((i.second.begin == -1) && (i.second.end == -1)) 
		{
			if (!is_first)
				cout << ", ";
			cout << i.first;
			is_first = false;
		}
	}
	cout << endl;
}

void GazTransNet::CurrentState(const unordered_map<int, CPipe>& pipes)
{
	for (const auto& i : pipes)
	{
		cout << "\n " << i.first << " Pipe (" << i.second.length << ") " << i.second.begin << " -> " << i.second.end;
	}
	cout << endl;
}

void GazTransNet::EstablishConnection(unordered_map<int, CPipe>& pipes, unordered_map<int, CCS>& cs)
{
	int selectPipe = 0;
	do
	{
		cout << "\nWhat kind of pipe to connect?\n\nList id pipes: ";
		ViewAllReadyPipe(pipes);
		selectPipe = CheckChoiceId(pipes);
		cout << "\nList id CS: ";
		ViewAllId(cs);

		cout << "From ";
		pipes[selectPipe].begin = CheckChoiceId(cs);

		cout << "Where ";
		pipes[selectPipe].end = CheckChoiceId(cs);

		cout << "\nExit?\n1. Yes\n2. No\nSelect - ";
	} while (CheckNum(1, 2) == 2);
	cout << endl;

	CurrentState(pipes);
}

void GazTransNet::ViewMatrix(const vector<int>& nodes)
{
	size = nodes.size();
	cout << endl << "\t";
	for (const auto& s : nodes)
	{
		cout << s << "\t";
	}
	cout << endl;
	int count = 0;

	for (const auto& s : nodes)
	{
		cout << s << "\t";
		for (size_t i = 0; i < size; i++)
		{
			cout << matrix[count][i] << "\t";
		}
		cout << endl;
		++count;
	}
}

void GazTransNet::FillingMatrix(const vector<pair<int, int>>& InOut, const vector<int>& nodes)
{
	int size = nodes.size();
	std::pair<int, int> io;
	for (const auto& i : InOut)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i.first == nodes[j])
				io.first = j;
			if (i.second == nodes[j])
				io.second = j;
		}
		matrix[io.first][io.second] = 1;
		matrix[io.second][io.first] = -1;
	}

	for (size_t i = 0; i < size; i++)
	{
		matrix[i][i] = 0; 
	}
}

bool GazTransNet::ZeroMatrix(const int& size)
{
	int t = 1;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] == 0)
				t *= 1;
			else
				t *= 0;
		}
	}
	return t;
}

int GazTransNet::SearchZeroHalfStepNodes(const vector<int>& nodes, deque<int> TopologicNodes)
{
	int size = nodes.size();
	int addNode = 0;
	int index = -1;
	int k = 1;
	vector <int> Included;
	for (size_t i = 0; i < size; i++)
	{
		k = 1;
		Included.clear();
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] != 1)
				k *= 1;
			else
				k *= 0;
			if (matrix[i][j] < 0)
			{
				Included.push_back(j);
			}
		}
		if (TopologicNodes.empty())
		{
			if (k == 1)
			{
				index = i;
				break;
			}
		}
		else
		{
			int q = 1;
			for (const int& t : TopologicNodes)
			{
				if (i != t)
					q *= 1;
				else
					q *= 0;
			}
			if (k == 1 && q == 1)
			{
				index = i;
				break;
			}
		}
	}

	if ((index == -1))
	{
		return addNode = -100;
	}
	else
	{
		addNode = nodes[index];

		for (size_t j = 0; j < size; j++)
		{
			matrix[index][j] = 0;
		}
		for (int i : Included)
		{
			matrix[i][index] = 0;
		}

		return addNode;
	}
}

void GazTransNet::DeleteGraph(unordered_map<int, CPipe>& pipes)
{
	for (auto& i : pipes)
	{
		if (i.second.repair == 0)
		{
			i.second.begin = -1;
			i.second.end = -1;
		}
		else
		{
			i.second.begin = -2;
			i.second.end = -2;
		}
	}
}

void BubbleSort(vector<int>& values) {
	for (size_t idx_i = 0; idx_i + 1 < values.size(); ++idx_i) {
		for (size_t idx_j = 0; idx_j + 1 < values.size() - idx_i; ++idx_j) {
			if (values[idx_j + 1] < values[idx_j]) {
				swap(values[idx_j], values[idx_j + 1]);
			}
		}
	}
}

void GazTransNet::TopologicalSorting(const unordered_map<int, CPipe>& pipes)
{
	vector <pair<int, int>> InOut;
	pair<int, int> io;
	for (const auto& i : pipes)
	{
		if (!(i.second.begin == -1 || i.second.end == -1 || i.second.begin == -2 || i.second.end == -2))
		{
			io.first = i.second.begin;
			io.second = i.second.end;
			cout << i.first << " Pipe " << io.first << " -> " << io.second << endl;
			InOut.push_back(io);
		}
	}

	vector<int> nodes;
	int add = 1;
	for (const auto& i : InOut)
	{
		add = 1;
		for (const int& j : nodes)
		{
			if (i.first != j)
				add *= 1;
			else
				add *= 0;
		}
		if (add == 1)
			nodes.push_back(i.first);

		add = 1;
		for (const int& j : nodes)
		{
			if (i.second != j)
				add *= 1;
			else
				add *= 0;
		}
		if (add == 1)
			nodes.push_back(i.second);
	}

	BubbleSort(nodes);

	size = nodes.size();
	matrix.resize(size, vector<int>(size));

	FillingMatrix(InOut, nodes);
	
	deque<int> TopologicNodes;
	bool loop = true;
	int addNode = 0;
	while ((!ZeroMatrix(size)) && loop)
	{
		addNode = SearchZeroHalfStepNodes(nodes, TopologicNodes);
		
		if (addNode == -100)
		{
			std::cout << "\nThe graph contains a loop\n";
			loop = false;
		}
		else
		{
			TopologicNodes.push_back(addNode);
		}
	}
	if (loop)
	{
		int k = 1;
		for (const int& i : nodes)
		{
			k = 1;
			for (const int& j : TopologicNodes)
			{
				
					k *= 0;
			}
			if (k == 1)
			{
				TopologicNodes.push_back(i);
			}
		}
	
		std::cout << "Result topological sorting: \n";
		bool is_first = true;
		while (!TopologicNodes.empty())
		{
			if (!is_first)
				cout << " -> ";
			cout  << TopologicNodes.back();
			TopologicNodes.pop_back();
			is_first = false;
		}
		cout << endl << endl;
	}

}