#pragma once
#include "CPipe.h"
#include "CCS.h"
#include <deque>
#include <unordered_map>

class GazTransNet
{
public:
	void EstablishConnection(unordered_map<int, CPipe>& pipes, unordered_map<int, CCS>& cs);
	void CurrentState(const unordered_map<int, CPipe>& pipes);
	void TopologicalSorting(const unordered_map<int, CPipe>& pipes);
	void DeleteGraph(unordered_map<int, CPipe>& pipes);
	void DeleteConnect(unordered_map<int, CPipe>& pipes);

private:
	vector<vector<int>>matrix;
	int size = 0;
	void ViewAllReadyPipe(const unordered_map<int, CPipe>& pipes);
	void ViewMatrix(const vector<int>& nodes);
	void FillingMatrix(const vector<pair<int, int>>& InOut, const vector<int>& nodes);
	bool ZeroMatrix(const int& size);
	int SearchZeroHalfStepNodes(const vector<int>& nodes, deque<int> TopologicNodes);

	vector<vector<int>> link;
	void ViewLink(const vector<int>& nodes);
	void FillingLink(const vector<pair<int, int>>& InOut, const vector<int>& nodes, const unordered_map<int, CPipe>& pipes);

	int bfs(int start, int end);
};

